#ifndef NEAT_INNOVATION_H
#define NEAT_INNOVATION_H

#include "neat_node.h"

/**
 * @brief Represents an connection in the NEAT algorithm.
 *
 * An connection is a directed connection between two nodes in the neural network.
 * Each connection has a unique ID.
 */
typedef struct t_neat_connection t_neat_connection;

/**
 * @brief Creates a new connection connecting the given source and target nodes.
 *
 * @param id Id of the connection
 * @param source Pointer to the source node of the connection.
 * @param target Pointer to the target node of the connection.
 * @return Pointer to a newly allocated connection, or NULL on allocation failure.
 */
t_neat_connection* neat_connection_new(int innovation_number, char* id, t_neat_node* source, t_neat_node* target);

/**
 * @brief Frees the memory associated with an connection.
 *
 * @param connection Pointer to the connection to delete. If NULL, does nothing.
 */
void neat_connection_free(void* connection);

/**
 * @brief Returns the innovation number of the connection.
 *
 * @param connection Pointer to the connection.
 * @return The connection innovation number, or -1 if the pointer is NULL.
 */
int neat_connection_innovation_number(const t_neat_connection* connection);

/**
 * @brief Returns the unique ID of the connection.
 *
 * @param connection Pointer to the connection.
 * @return The connection ID, or -1 if the pointer is NULL.
 */
char* neat_connection_id(const t_neat_connection* connection);

/**
 * @brief Returns the source node of the connection.
 *
 * @param connection Pointer to the connection.
 * @return Pointer to the source node, or NULL if the connection pointer is NULL.
 */
t_neat_node* neat_connection_source(const t_neat_connection* connection);

/**
 * @brief Returns the target node of the connection.
 *
 * @param connection Pointer to the connection.
 * @return Pointer to the target node, or NULL if the connection pointer is NULL.
 */
t_neat_node* neat_connection_target(const t_neat_connection* connection);

#endif /* NEAT_INNOVATION_H */
