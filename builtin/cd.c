/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/12 23:42:53 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_path(char **envp, char *varenv)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], varenv, ft_strlen(varenv)) == 0)
		{
			path = ft_strdup(envp[i], 0);
			return (path);
		}
		i++;
	}
	return (NULL);
}

int	ft_cd(t_test **lst, char **envp)
{
	char	*path;
	char	*home;
	char	*oldpwd;
	char	*pwd;

	home = find_path(envp, "HOME=");
	oldpwd = find_path(envp, "OLDPWD=");
	pwd = find_path(envp, "PWD=");
	if (!(*lst)->next)
		path = home;
	else if (ft_strncmp((*lst)->next->content, "-", 1) == 0)
		path = oldpwd;
	else
		path = (*lst)->next->content;
	if (chdir(path) == -1)
	{
		ft_printf("cd: %s: %s\n", path, strerror(errno));
		(*lst)->exit_code = 1;
	}
	else
	{
		if (ft_strncmp((*lst)->next->content, "-", 1) == 0)
			ft_printf("%s\n", oldpwd + 7);
		else
			ft_printf("%s\n", path + 5);
		(*lst)->exit_code = 0;
	}
	free(home);
	free(oldpwd);
	free(pwd);
	return ((*lst)->exit_code);
}

// /* notes :
// cd /
// cd ///////
// cd = cd ~
// cd uvbhjn = no such file or directory
// cd ..
// cd .
// cd
// cd ~
// cd e/abc/e/abc = relative path
// cd e/abc = absolute path
// cd split sur les paths et lster un par un les dossiers
// //setenv("PWD", path_max, 1); ? utile ou pas ?
// */