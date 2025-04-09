#include "minishell.h"

void    ft_parse_error(t_parse_error_type type)
{
    g_minishell.parse_error.type = type;
}

void    ft_manage_parser_error(void)
{
    t_parse_error_type  type;
    t_token_type    token_type;
    char    **types;

    types = (char *[]){"T_IDENTIFIER",
		"<", ">", "<<", ">>", "|", "(", ")", "&&", "||", "newline"};
    type = g.minishell.parser_error.type;
    (void)token_type;
    (void)types;
    if(type)
    {
        if(type == E_SYNTAX)
        {
            if(!g.minishell.current_token)
                token_type = T_NL;
            else
                token_type = g.minishell.cureent_token->type;
            ft_putsrt_fd("minishell: syntax error near unexpected token `", 2);
            ft_putsrt_fd(types[token_type], 2);
            ft_putsrt_fd("'\n", 2);
            g.minishell.exit_err = 258; 
        }
        ft_clear_ast(&g.minishell.ast);
        ft_bzero(&g.minishell.parser_error, sizeof(t_parse_error));
    }
}
