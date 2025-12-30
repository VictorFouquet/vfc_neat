#include <criterion/criterion.h>
#include <signal.h>
#include "neat_node.h"


Test(neat_node, neat_node_new_should_return_pointer_to_new_node_struct)
{
    t_neat_node* node1 = neat_node_new(0, NEAT_NODE_INPUT);
    cr_assert_not_null(node1);

    t_neat_node* node2 = neat_node_new(1, NEAT_NODE_HIDDEN);
    cr_assert_not_null(node2);

    t_neat_node* node3 = neat_node_new(2, NEAT_NODE_OUTPUT);
    cr_assert_not_null(node3);
    
    neat_node_free(node1);
    neat_node_free(node2);
    neat_node_free(node3);
}

Test(neat_node, neat_node_free_should_free_the_neat_node)
{
    t_neat_node* node = neat_node_new(0, NEAT_NODE_INPUT);
    cr_assert_not_null(node);
    
    neat_node_free(node);
}

Test(neat_node, neat_node_free_should_abort_if_null, .signal = SIGABRT)
{
    neat_node_free(NULL);
}

Test(neat_node, neat_node_id_returns_node_id)
{
    unsigned int id = 123;
    t_neat_node* node = neat_node_new(id, NEAT_NODE_INPUT);

    cr_assert_eq(neat_node_id(node), id);
    neat_node_free(node);
}

Test(neat_node, neat_node_id_should_abort_if_null, .signal = SIGABRT)
{
    neat_node_id(NULL);
}

Test(neat_node, neat_node_type_should_return_neat_node_type)
{
    t_neat_node* node1 = neat_node_new(0, NEAT_NODE_INPUT);
    cr_assert_eq(neat_node_type(node1) , NEAT_NODE_INPUT);

    t_neat_node* node2 = neat_node_new(1, NEAT_NODE_HIDDEN);
    cr_assert_eq(neat_node_type(node2) , NEAT_NODE_HIDDEN);

    t_neat_node* node3 = neat_node_new(2, NEAT_NODE_OUTPUT);
    cr_assert_eq(neat_node_type(node3) , NEAT_NODE_OUTPUT);

    neat_node_free(node1);
    neat_node_free(node2);
    neat_node_free(node3);
}

Test(neat_node, neat_node_type_should_return_invalid_type_if_node_is_null)
{
    cr_assert_eq(neat_node_type(NULL), NEAT_NODE_INVALID);
}
