#include "minishell.h"

static int   ft_writer_heredoc(char *str, size_t i, int fd)
{  
    size_t  start;
    char    *tmp;

    start = ++i;
    if (str[i] == '?')
        return (ft_putnbr_fd(g_minishell.exit_s, fd), 2);
    while (str[i] && str[i] != '$' && str[i] != ' ')
        i++;
    if (i != start)
    {
        tmp = ft_garbage_collector(ft_substr(str, start, i), false);
        tmp = ft_get_envlst_val(tmp);
        if (tmp)
            ft_putstr_fd(tmp,fd);
    }
    return (i);
}

void    ft_expand_heredoc(char *str, int fd)
{
    size_t  i;
    
    i = 0;
    while(str[i])
    {
        if (str[i] == '$')
            i += ft_writer_heredoc(str, i, fd);
        else
            i += (ft_putchar_fd(str[i], fd), 1);
    }
    ft_putchar_fd('\n', fd);
}

