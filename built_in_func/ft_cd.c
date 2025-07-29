/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:21:01 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 12:21:14 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_change_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	return (ft_update_envlist("PWD", cwd, false), 0);
}

static int	ft_cd_home(void)
{
	char	*home;

	ft_update_envlist("OLDPWD", ft_envlist_value("PWD"), false);
	home = ft_envlist_value("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == ENO_SUCCESS)
		return (ft_update_envlist("PWD", home, false), 0);
	return (1);
}

static int	ft_cd_err_msg(char *err_msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	ft_cd(char *path)
{
	if (!path)
		return (ft_cd_home());
	if (chdir(path) != ENO_SUCCESS)
		return (ft_cd_err_msg(path));
	ft_update_envlist("OLDPWD", ft_envlist_value("PWD"), false);
	return (ft_change_pwd());
}
