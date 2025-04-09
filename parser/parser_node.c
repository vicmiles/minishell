#include "minishell.h"

t_node_type ft_node_type(t_token_type token)
{
    if (type == T_AND)
        return (N_AND);
    if (type == T_OR)
        return (N_OR);
    return (N_PIPE);
}

t_io_node   ft_io_type(t_token_type type)
{
    if (type == T_LESS)
        return (IO_IN);
    if (type == T_GREAT)
        return (IO_OUT);
    if (type == D_LESS)
        return (IO_HEREDOC);
    return (IO_APPEND);
}

t_node  *ft_new_node(t_node_type type)
{
    t_node  *new_node;
    new_node = (t_node *)ft_calloc(1, sizeof(t_node));
    if (!new_node)
        return (NULL);
    new_node->type = type;
    return (new_node);
}

t_io_node   ft_new_ionode(t_token_type  type, char *value)
{
    t_io_node *new_node;

    new_node = (t_io_node *)ft_calloc(1, sizeof(t_io_node));
    if(!new_node)
        return (NULL);
    new_node->type = ft_io_type(type);
    new_node->value = ft_strdup(value);
    if (!new_node->value)
            return(free(new_node), NULL);
    return (new_node);
}

void    ft_append_ionode(t_io_node **list, t_io_node *new)
{
    t_io_node   *current_node;

    if(!*list)
    {   
        *list = new;
        return ;
    }
    current_node = *list;
    while (current_node && current_node -> next)
        current_node = current_node -> next;
    current_node -> next = new;
}