#include <criterion/criterion.h>
#include <signal.h>
#include <string.h>
#include "str_utils.h"

#include "neat_connection.h"


//t_neat_connection* neat_connection_new(int innovation_number, char* id, t_neat_node* source, t_neat_node* target);
Test(neat_connection, neat_connection_new_should_return_a_pointer_to_a_connection_struct)
{
    t_neat_node* n0 = neat_node_new(0, NEAT_NODE_INPUT);
    t_neat_node* n1 = neat_node_new(1, NEAT_NODE_OUTPUT);
    t_neat_node* n2 = neat_node_new(1, NEAT_NODE_HIDDEN);
    t_neat_node* n3 = neat_node_new(1, NEAT_NODE_HIDDEN);

    // i -> o
    t_neat_connection* c1 = neat_connection_new(0, "0,1", n0,  n1);
    cr_assert_not_null(c1);

    // i -> h
    t_neat_connection* c2 = neat_connection_new(1, "0,2", n0,  n2);
    cr_assert_not_null(c2);

    // h -> h
    t_neat_connection* c3 = neat_connection_new(2, "2,3", n2, n3);
    cr_assert_not_null(c3);

    // h -> o
    t_neat_connection* c4 = neat_connection_new(3, "2,1", n2, n1);
    cr_assert_not_null(c4);

    neat_node_free(n0);
    neat_node_free(n1);
    neat_node_free(n2);
    neat_node_free(n3);

    neat_connection_free(c1);
    neat_connection_free(c2);
    neat_connection_free(c3);
    neat_connection_free(c4);
}

Test(neat_node, neat_connection_new_should_abort_if_id_is_null, .signal = SIGABRT)
{
    neat_connection_new(0, NULL, neat_node_new(0, NEAT_NODE_INPUT), neat_node_new(1, NEAT_NODE_OUTPUT));
}

Test(neat_node, neat_connection_new_should_abort_if_source_is_null, .signal = SIGABRT)
{
    neat_connection_new(0, "0,1", NULL, neat_node_new(1, NEAT_NODE_OUTPUT));
}

Test(neat_node, neat_connection_new_should_abort_if_target_is_null, .signal = SIGABRT)
{
    neat_connection_new(0, "0,1", neat_node_new(0, NEAT_NODE_INPUT), NULL);
}

Test(neat_node, neat_connection_new_should_abort_if_input_node_is_output, .signal = SIGABRT)
{
    neat_connection_new(0, "0,1", neat_node_new(0, NEAT_NODE_OUTPUT), neat_node_new(1, NEAT_NODE_OUTPUT));
}

Test(neat_node, neat_connection_new_should_abort_if_output_node_is_input, .signal = SIGABRT)
{
    neat_connection_new(0, "0,1", neat_node_new(0, NEAT_NODE_INPUT), neat_node_new(1, NEAT_NODE_INPUT));
}

Test(neat_node, neat_connection_new_should_abort_if_input_and_output_are_equal, .signal = SIGABRT)
{
    t_neat_node* node = neat_node_new(0, NEAT_NODE_HIDDEN);
    neat_connection_new(0, "0,1", node, node);
}

// void neat_connection_free(void* connection);
Test(neat_connection, neat_connection_free_should_free_the_neat_connection)
{
    char* id = str_utils_strdup("0,1");
    t_neat_node* input  =  neat_node_new(0, NEAT_NODE_INPUT);
    t_neat_node* output =  neat_node_new(0, NEAT_NODE_OUTPUT);
    t_neat_connection* connection = neat_connection_new(0, id, input, output);
    cr_assert_not_null(connection);
    
    free(id);
    neat_node_free(input);
    neat_node_free(output);
    neat_connection_free(connection);
}

Test(neat_connection, neat_connection_free_should_abort_if_null, .signal = SIGABRT)
{
    neat_connection_free(NULL);
}

// char* neat_connection_id(const t_neat_connection* connection);
Test(neat_connection, neat_connection_id_should_return_connection_id)
{
    char* id = "0,1";
    t_neat_node* in = neat_node_new(0, NEAT_NODE_INPUT);
    t_neat_node* out = neat_node_new(1, NEAT_NODE_OUTPUT);
    t_neat_connection* connection = neat_connection_new(0, id, in, out);

    cr_assert_str_eq(id, neat_connection_id(connection));

    neat_node_free(in);
    neat_node_free(out);
    neat_connection_free(connection);
}

Test(neat_connection, neat_connection_id_should_abort_if_connection_is_null, .signal = SIGABRT)
{
    neat_connection_id(NULL);
}

// int neat_connection_innovation_number(const t_neat_connection* connection);
Test(neat_connection, neat_connection_innovation_number_should_return_connection_id)
{
    int innov_number = 0;
    t_neat_node* in = neat_node_new(0, NEAT_NODE_INPUT);
    t_neat_node* out = neat_node_new(1, NEAT_NODE_OUTPUT);

    t_neat_connection* connection = neat_connection_new(0, "0,1", in, out);
    
    cr_assert_eq(innov_number, neat_connection_innovation_number(connection));

    neat_node_free(in);
    neat_node_free(out);
    neat_connection_free(connection);
}

Test(neat_connection, neat_connection_innovation_number_should_abort_if_connection_is_null, .signal = SIGABRT)
{
    neat_connection_innovation_number(NULL);
}

// t_neat_node* neat_connection_source(const t_neat_connection* connection);
Test(neat_connection, neat_connection_source_should_return_source_node)
{
    t_neat_node* src = neat_node_new(0, NEAT_NODE_INPUT);
    t_neat_node* tgt = neat_node_new(0, NEAT_NODE_OUTPUT);

    t_neat_connection* connection = neat_connection_new(0, "0,1", src, tgt);
    cr_assert_eq(src, neat_connection_source(connection));

    neat_node_free(src);
    neat_node_free(tgt);
    neat_connection_free(connection);
}

Test(neat_connection, neat_connection_source_should_abort_if_connection_is_null, .signal = SIGABRT)
{
    neat_connection_source(NULL);
}

// t_neat_node* neat_connection_target(const t_neat_connection* connection);
Test(neat_connection, neat_connection_target_should_return_target_node)
{
    t_neat_node* src = neat_node_new(1, NEAT_NODE_INPUT);
    t_neat_node* tgt = neat_node_new(0, NEAT_NODE_OUTPUT);
    char* id = "0,1";
    t_neat_connection* connection = neat_connection_new(0, id, src, tgt);
    cr_assert_eq(tgt, neat_connection_target(connection));
    
    neat_node_free(src);
    neat_node_free(tgt);
    neat_connection_free(connection);
}

Test(neat_connection, neat_connection_target_should_abort_if_connection_is_null, .signal = SIGABRT)
{
    neat_connection_target(NULL);
}
