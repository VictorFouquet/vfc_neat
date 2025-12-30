#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "log_utils.h"
#include "neat_node.h"

typedef struct t_neat_node
{
    unsigned int   id;
    t_neat_node_type type;
} t_neat_node;

t_neat_node* neat_node_new(unsigned int id, t_neat_node_type node_type)
{
    t_neat_node* node = malloc(sizeof(t_neat_node));
    
    if (!node) return NULL;

    node->id = id;
    node->type = node_type;
    
    log_utils_debug(
        "neat_node_new",
        "Created node %p (id=%d, type=%d)",
        node, node->id, node->type
    );

    return node;
}

void neat_node_free(t_neat_node* node)
{
    assert(node);

    log_utils_debug("neat_node_free", "Free node %p (id=%d)\n", node, node->id);
    
    free(node);
}

int neat_node_id(const t_neat_node* node)
{
    assert(node);
    return node ? (int)(node->id) : -1;
}

t_neat_node_type neat_node_type(const t_neat_node* node)
{
    return node ? node->type : NEAT_NODE_INVALID;
}
