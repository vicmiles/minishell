#include "minishell.h"

char	*ft_dollar_handle(char *str, size_t *i)
{
	size_t	start;
	char	*var;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_minishell.exit_s));
	}
	else if (!ft_valid_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (ft_valid_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = ft_get_envlst_val(var);
	if (!env_val)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_val));
}

static char	*ft_cmd_expand(char *str)
{
	char	*res;
	size_t	i;

	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			res = ft_strjoin_f(res, ft_squote_handle(str, &i));
		else if (str[i] == '"')
			res = ft_strjoin_f(res, ft_dquote_handle(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin_f(res, ft_dollar_handle(str, &i));
		else
			res = ft_strjoin_f(res, ft_str_handle(str, &i));
	}
	return (res);
}

char	**ft_expand(char *str)
{
	char	**expand;
	char	**glob;
	size_t	i;

	str = ft_cmd_expand(str);
	if (!str)
		return (NULL);
	str = ft_clean_empty_str(str);
	if (!str)
		return (NULL);
	expand = ft_expand_split(str);
	free(str);
	if (!expand)
		return (NULL);
	glob = ft_file_expander(expand);
	if (!glob)
		return (NULL);
	i = 0;
	while (glob[i])
	{
		glob[i] = ft_unquote(glob[i]);
		i++;
	}
	return (glob);
}