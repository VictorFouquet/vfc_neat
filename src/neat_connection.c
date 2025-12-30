#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "neat_connection.h"
#include "hashtable.h"
#include "str_utils.h"
#include "log_utils.h"

typedef struct t_neat_connection 
{
    char*        id;
    int          innovation_number;
    t_neat_node* source;
    t_neat_node* target;
} t_neat_connection;

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

t_neat_connection* neat_connection_new(int innovation_number, char* id, t_neat_node* source, t_neat_node* target)
{
    assert(id);
    assert(source);
    assert(target);
    assert((neat_node_type(source) == NEAT_NODE_INPUT  || neat_node_type(source) == NEAT_NODE_HIDDEN));
    assert((neat_node_type(target) == NEAT_NODE_OUTPUT || neat_node_type(target) == NEAT_NODE_HIDDEN));
    assert(source != target);

    t_neat_connection* connection = malloc(sizeof(t_neat_connection));
    assert(connection);
    
    connection->innovation_number = innovation_number;
    connection->id = str_utils_strdup(id);
    connection->source = source;
    connection->target = target;

    return connection;
}

void neat_connection_free(void* connection)
{
    assert(connection);
    free(neat_connection_id((t_neat_connection*)connection));
    free(connection);
}

int neat_connection_innovation_number(const t_neat_connection* connection)
{
    assert(connection);
    return connection->innovation_number;
}

char* neat_connection_id(const t_neat_connection* connection)
{
    assert(connection);
    return connection->id;
}

t_neat_node* neat_connection_source(const t_neat_connection* connection)
{
    assert(connection);
    return connection->source;
}

t_neat_node* neat_connection_target(const t_neat_connection* connection)
{
    assert(connection);
    return connection->target;
}
