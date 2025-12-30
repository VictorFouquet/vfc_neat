#ifndef NEAT_INNOVATION_BUILDER_H
#define NEAT_INNOVATION_BUILDER_H

#include "hashtable.h"
#include "linked_list.h"
#include "neat_connection.h"
#include "neat_node.h"


bool neat_innovation_tracker_init(size_t inputs_count, size_t outputs_count);
void neat_innovation_tracker_destroy();

t_linked_list* neat_innovation_tracker_get_init_nodes();

t_neat_node* neat_innovation_tracker_create_node(t_neat_connection* connection);
t_neat_node* neat_innovation_tracker_get_node(unsigned int id);

t_neat_connection* neat_innovation_tracker_create_connection(t_neat_node* source, t_neat_node* target);
t_neat_connection* neat_innovation_tracker_get_connection(char* id);

#endif /* NEAT_INNOVATION_BUILDER_H */