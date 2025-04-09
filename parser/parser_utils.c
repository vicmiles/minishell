#include "minishell.h"

void    ft_get_next_token(void)
{
    g_minishell.current_token = g_minishell.current_token -> next;
}

bool ft_curr_token_binop(void)
{
    t_token_type token;

    if (!g_minishell.current_token)
        return (false);
    type = g_minishell.current_token->type;
    if (type == T_PIPE || type == T_AND || type == T_OR)
        return (true);
    return (false);
}

bool ft_isredir(t_token_type token)
{
    if (type == T_LESS || type == T_GREAT 
        || type == TDLESS || type == T_DGREAT)
        return (true);
    return (false);
}

int ft_prior(t_token_type token)
{
    if (type == T_OR || type == T_AND)
        return (0);
    return (1);
}

int ft_curtoken_prior(void)
{
    return (ft_prior(g_minishell.current_token->type));
}