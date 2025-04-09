#include "minishell.h"

bool    ft_contain_star(char *str)
{
    size_t  i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '*')
            return (true);
        i++;
    }
    return (false);
}

size_t  ft_arraystr_len(char **array_str)
{
    size_t  i;

    i = 0;
    while (array_str[i])
        i++;
    return (i);
}

size_t  ft_count_match(char *pattern)
{
    DIR *dir;
    size_t  count_match;
    struct dirent   *entry;

    count_match = 0;
    dir = opendir(".");
	entry = readdir(dir);
    while (entry)
    {
        if (ft_star_match(pattern, entry->d_name))
            count_match++;
        entry = readdir(dir);
    }
    closedir(dir);
    return(count_match);
}

static size_t  ft_arraystr_count(char **array_str)
{
    size_t  i;
    size_t  j;
    size_t str_count;

    i = 0;
    str_count = 0;
    while (array_str[i])
    {
        j = 0;
        while (array_str[i][j])
        {
            j++;
            str_count += j;
            i++;
        }
        return (str_cout);
    }
}

char **ft_arraystr_join(char **array_str)
{
    size_t  i;
    size_t  j;
    size_t str_count;
    char    *join;

    str_count = ft_arraystr_count(array_str);
    join = (char **)ft_calloc(str_count + 1, sizeof(char *));
    i = 0;
    str_count = 0;
    while(array_str[i])
    {
        j = 0;
        while (array_str[i][j])
        {
            join[array_str + j] = ft_strdup(array_str[i][j]);
            j++;
        }
        str_count += j;
        i++;
    }
    return (ft_free_char3(array_str), join);
}