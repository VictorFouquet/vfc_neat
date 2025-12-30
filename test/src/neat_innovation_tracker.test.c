#include <criterion/criterion.h>
#include <signal.h>

#include "neat_innovation_tracker.h"

// bool neat_innovation_tracker_init(size_t inputs_count, size_t outputs_count);
Test(neat_innovation_tracker, neat_innovation_tracker_init_with_valid_inputs_and_outputs_should_indicate_success)
{
    cr_assert(neat_innovation_tracker_init(1, 1));
}

Test(neat_innovation_tracker, neat_innovation_tracker_init_with_empty_inputs_or_outputs_should_not_indicate_success)
{
    cr_assert_not(neat_innovation_tracker_init(1, 0));
    cr_assert_not(neat_innovation_tracker_init(0, 1));
    cr_assert_not(neat_innovation_tracker_init(0, 0));
}

Test(neat_innovation_tracker, neat_innovation_tracker_init_called_twice_with_same_arguments_should_indicate_success)
{
    cr_assert(neat_innovation_tracker_init(3, 1));
    cr_assert(neat_innovation_tracker_init(3, 1));
}

Test(neat_innovation_tracker, neat_innovation_tracker_init_called_twice_with_different_arguments_should_not_indicate_success)
{
    cr_assert(neat_innovation_tracker_init(2, 2));
    cr_assert_not(neat_innovation_tracker_init(2, 1));
}

// void neat_innovation_tracker_destroy();

// t_linked_list* neat_innovation_tracker_get_init_nodes();

// t_neat_node* neat_innovation_tracker_create_node(t_neat_connection* connection);
// t_neat_node* neat_innovation_tracker_get_node(unsigned int id);

// t_neat_connection* neat_innovation_tracker_create_connection(t_neat_node* source, t_neat_node* target);
// t_neat_connection* neat_innovation_tracker_get_connection(char* id);