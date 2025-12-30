#ifndef NEAT_NODE_H
#define NEAT_NODE_H

/**
 * @file neat_node.h
 * @brief Defines a NEAT node structure and basic operations.
 *
 * Provides creation, deletion, and accessors for nodes in a NEAT network.
 */

/* Forward declarations */
typedef struct t_neat_node t_neat_node;
typedef enum t_neat_node_type
{
    NEAT_NODE_INPUT,
    NEAT_NODE_HIDDEN,
    NEAT_NODE_OUTPUT,
    NEAT_NODE_INVALID = -1
} t_neat_node_type;

/**
 * @brief Creates a new NEAT node.
 *
 * Allocates memory and initializes a node with the given type and assign it a global id.
 *
 * @param node_id Unique identifier for the node.
 * @param node_type Type of the node (INPUT, HIDDEN, OUTPUT).
 * @return Pointer to the newly created node, or NULL if allocation fails.
 */
t_neat_node* neat_node_new(unsigned int id, t_neat_node_type node_type);

/**
 * @brief Frees a NEAT node.
 *
 * Deallocates the memory associated with the node.
 *
 * @param node Pointer to the node to free. If NULL, does nothing.
 */
void neat_node_free(t_neat_node* node);

/**
 * @brief Returns the ID of a node.
 *
 * @param node Pointer to the node.
 * @return Node ID, or -1 if node is NULL.
 */
int neat_node_id(const t_neat_node* node);

/**
 * @brief Returns the type of a node.
 *
 * @param node Pointer to the node.
 * @return Node type, or NEAT_NODE_TYPE_INVALID if node is NULL.
 */
t_neat_node_type neat_node_type(const t_neat_node* node);

#endif /* NEAT_NODE_H */
