#include <stdio.h>

#include "log_utils.h"
#include "neat_innovation_tracker.h"
#include "neat_strategy.h"

typedef struct t_neat_innovation_tracker
{
    t_linked_list* nodes;
    t_linked_list* input_nodes;
    t_linked_list* hidden_nodes;
    t_linked_list* output_nodes;
    t_linked_list* io_nodes;

    t_hashtable* connections;
    t_hashtable* node_innovations;

    size_t input_count;
    size_t output_count;

    unsigned int global_node_id;
    unsigned int global_connexion_id;
} t_neat_innovation_tracker;


static t_neat_innovation_tracker* singleton;


static char* neat_connection_get_id(const t_neat_node* source, const t_neat_node* target)
{
    char* id = malloc(32);
    if (!id) return NULL;

    snprintf(id, 32, "%d,%d", neat_node_id(source), neat_node_id(target));

    return id;
}

static unsigned int neat_connection_hash_id(char* key)
{
    int source_id, target_id;

    if (sscanf(key, "%d,%d", &source_id, &target_id) == 2)
    {
        // See Cantor pairing
        return (source_id + target_id) * (source_id + target_id + 1) / 2 + target_id;
    }
    else
    {
        return 0;
    }
}

bool neat_innovation_tracker_init(size_t inputs_count, size_t outputs_count)
{
    // Init called more than once but with same arguments
    if
    (
        singleton != NULL
        && inputs_count == singleton->input_count
        && outputs_count == singleton->output_count
    )
        return true;

    // Init called more than once with different arguments,
    // or called once with invalid arguments
    if
    (
        singleton != NULL
        || inputs_count == 0
        || outputs_count == 0
    )
        return false;

    singleton = calloc(1, sizeof(t_neat_innovation_tracker));

    // Malloc failure
    if (singleton == NULL) return false;

    singleton->input_count = inputs_count;
    singleton->output_count = outputs_count;

    singleton->global_node_id = 0;
    singleton->global_connexion_id = 0;

    singleton->connections = hashtable_new((size_t)1e6, neat_connection_hash_id);
    if (!singleton->connections) goto init_failure;

    singleton->node_innovations = hashtable_new((size_t)1e6, neat_connection_hash_id);
    if (!singleton->node_innovations) goto init_failure;

    // Global owner of nodes structs
    singleton->nodes = linked_list_new();
    if (singleton->nodes == NULL) goto init_failure;

    singleton->io_nodes  = linked_list_new();
    if (singleton->io_nodes == NULL) goto init_failure;

    singleton->input_nodes  = linked_list_new();
    if (singleton->input_nodes == NULL) goto init_failure;

    singleton->hidden_nodes = linked_list_new();
    if (singleton->hidden_nodes == NULL) goto init_failure;

    singleton->output_nodes = linked_list_new();
    if (singleton->output_nodes == NULL) goto init_failure;
    
    
    for (size_t i = 0; i < inputs_count; i++)
    {
        t_neat_node* node = neat_node_new(singleton->global_node_id++, NEAT_NODE_INPUT);
        if (node == NULL) goto init_failure;
        if (
            linked_list_add(singleton->nodes, node) == NULL
            || linked_list_add(singleton->input_nodes, node) == NULL
            || linked_list_add(singleton->io_nodes, node) == NULL
        ) {
            neat_node_free(node);
            goto init_failure;
        }
    }

    for (size_t i = 0; i < outputs_count; i++)
    {
        t_neat_node* node = neat_node_new(singleton->global_node_id++, NEAT_NODE_OUTPUT);
        if (node == NULL) goto init_failure;
        
        if (
            linked_list_add(singleton->nodes, node) == NULL
            || linked_list_add(singleton->output_nodes, node) == NULL
            || linked_list_add(singleton->io_nodes, node) == NULL
        ) {
            neat_node_free(node);
            goto init_failure;
        }
    }

    return true;

    init_failure:
        neat_innovation_tracker_destroy();
        return false;
}


void neat_innovation_tracker_destroy()
{
    if (singleton == NULL)
        return;

    linked_list_free(singleton->nodes, neat_on_node_delete);
    linked_list_free(singleton->io_nodes, NULL);
    linked_list_free(singleton->input_nodes, NULL);
    linked_list_free(singleton->hidden_nodes, NULL);
    linked_list_free(singleton->output_nodes, NULL);

    hashtable_free(singleton->connections, neat_on_connection_free);
    hashtable_free(singleton->node_innovations, NULL);

    free(singleton);
    singleton = NULL;
}

t_linked_list* neat_innovation_tracker_get_init_nodes()
{
    if (singleton == NULL) return NULL;
    return singleton->io_nodes;
}

t_neat_node* neat_innovation_tracker_create_node(t_neat_connection* connection)
{
    if (singleton == NULL || connection == NULL) return NULL;

    char* connection_id = neat_connection_id(connection);

    t_neat_node* node = hashtable_entry_get(singleton->node_innovations, connection_id);
    if (node != NULL) return node;

    node = neat_node_new(singleton->global_node_id++, NEAT_NODE_HIDDEN);

    if (node == NULL) return NULL;

    if (
        linked_list_add(singleton->nodes, node) == NULL
        || linked_list_add(singleton->hidden_nodes, node) == NULL
        || hashtable_entry_set(singleton->node_innovations, connection_id, node) == false
    ) {
      neat_node_free(node);
      return NULL;
    }

    return node;
}

t_neat_node* neat_innovation_tracker_get_node(unsigned int id)
{
    if (singleton == NULL || singleton->nodes == NULL) return NULL;
    t_neat_node* node = linked_list_value(linked_list_at(singleton->nodes, id));
    return node;
}

t_neat_connection* neat_innovation_tracker_create_connection(t_neat_node* source, t_neat_node* target)
{
    if (singleton == NULL) return NULL;
    log_utils_debug(
        "neat_innovation_tracker_create_connection",
        "Starting connection creation from nodes %p and %p",
        source, target
    );
    
    char* id = neat_connection_get_id(source, target);
    log_utils_debug(
        "neat_innovation_tracker_create_connection",
        "Generate id %s for new connection",
        id
    );
    
    t_neat_connection* connection = hashtable_entry_get(singleton->connections, id);

    if (connection != NULL)
    {
        free(id);
        return connection;
    }

    connection = neat_connection_new(singleton->global_connexion_id++, id, source, target);
    
    log_utils_debug("neat_innovation_tracker_create_connection", "Create connection %p", connection);
    
    if (connection == NULL)
    {
        free(id);
        return NULL;
    }

    if (hashtable_entry_set(singleton->connections, id, connection) == false)
    {
        neat_connection_free(connection);
        return NULL;
    }
    free(id);
    return connection;
}

t_neat_connection* neat_innovation_tracker_get_connection(char* id)
{
    if (id == NULL || singleton == NULL || singleton->connections == NULL)
    {
        return NULL;
    }

    return hashtable_entry_get(singleton->connections, id);
}
