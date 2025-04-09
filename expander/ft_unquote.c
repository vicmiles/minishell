#include "minishell.h"

static size_t   ft_unquot_len(char *str)
{
    size_t  i;
    size_t  len;
    char    quote;

    i = 0;
    len = 0;
    quote = 0;
    while(str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            if (!quote)
                quote = str[i++];
            else if (str[i] == quote)
                quote = ((i++) && 0);
            else
                len += (i++ || 1);
        }
        else
            len += (i++ || 1);
    }
    return (len);
}

static void ft_unquot_copy(char *str, size_t *i, char *res, size_t *j)
{
    char    quote;
    
    quote = str[(*i)++];
    while (str[*i] != qoute)
        res[(*j)++] = str[(*i)++];
    (*i)++;
}

char    *ft_unquote(char *str)
{
    char    *res;
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    res = ft_calloc(1 + ft_unquot_len(str), sizeof(char));
    if (!res)
        return (NULL);
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
            ft_unquot_copy(str, &i, res, &j);
        else
            res[j++] = str[i++];
    }
    return (free(str), res);
}