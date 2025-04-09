#include "minishell.h"

t_token *ft_lexer(void)
{
    char *line;
    t_token *token_list;

    line = g_minishell.line;
    token_list = ft_lexer_handler(line);
    free(line);
    g_minishell.line = NULL;
    return (token_list);
}