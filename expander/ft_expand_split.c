#include "minishell.h"

static void   ft_skip_word(char const *str, size_t *i)
{
    char    *quote;

    while (str[*i] && str[*i] != ' ')
    {
        if (str[*i] != '\'' && str[*i] != '"')
            (*i)++;
        else
        {
            quote = str[(*i)++];
            while (str[*i] != quote)
                (*i)++;
            (*i)++;
        }
    }
}

static char ft_memory_allocate(char const *str, char **strs)
{
    size_t  char;
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
        {
            start = i;
            ft_skip_word(str, &i);
            strs[j] = ft_calloc(i - start + 1, sizeof(char));
            if (!strs[j])
                return NULL;
            j++;
        }
        while (str[i] && str[i] == ' ')
            i++;
    }
    return (strs);
}

static void ft_word_fill(const char *str, char **strs, size_t *i, size_t j)
{
    char    quote;
    size_t  i;

    i = 0;
    while (s[*i] && s[*i] != ' ')
    {
        if (s[*i] != '\'' && s[*i] != '"')
            strs[j][i++] = s[(*i)++];
        else
        {
            quote = s[(*i)++];
            strs[j][i++] = quote;
            while (s[*i] != quote)
                strs[j][i++] = s[(*i)++];
            strs[j][i++] = s[(*i)++];
        }
    }
}

static char **ft_fill(const char *str, char **strs)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (str[i] && strs[i])
    {
        if (str[i] != ' ')
        {
            ft_word_fill(str, strs, &i, j);
            j++;
        }
        while (str[i] && str[i] == ' ')
            i++;
    }
    return (strs);
}

char    **ft_expand_split(const char *str)
{
    size_t  count;
    char    **strs;
    char    **temp;
    size_t  i;

    if (!str)
        return (NULL);
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] != ' ' && ++count)
            ft_skip_word(s, &i);
        while (str[i] && str[i] == ' ')
            i++;
    }
    strs = ft_calloc(count + 1, sizeof(char *));
    temp = strs;
    strs = ft_memory_allocate(str, strs);
    if (!strs || !count)
        return (ft_free_char2(temp), NULL);
    return (ft_fill(str, strs)); 
}
