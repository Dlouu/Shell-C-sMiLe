/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/15 13:33:53 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(t_ms *ms)
{
	char	*old_path;
	char	*new_path;
	t_token	**tk;

	tk = ms->token;
	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (ft_putendl_fd("old_path unset je crois", STDERR_FILENO), 1); // vérifier le message d'erreur
	if (!(*tk)->next || ft_strcmp((*tk)->next->content, "~") == 0)
	{
		if (chdir(find_env_value(ms->env, "HOME")) == -1)
			return (ft_putendl_fd("cd: HOME not set", STDERR_FILENO), 1);
	}
	else if (chdir((*tk)->next->content) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd((*tk)->next->content, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (1);
	}
	replace_env_value(ms->env, "OLDPWD", old_path);
	new_path = getcwd(NULL, 0);
	replace_env_value(ms->env, "PWD", new_path);
	return (0);
}

		// if (errno == 2)
		// {
		// 	printf("minishell: cd: %s: No such file or directory\n", (*tk)->next->content);
		// 	return (1);
		// }
		// if (errno == 13)
		// {
		// 	printf("minishell: cd: %s: Permission denied\n", (*tk)->next->content);
		// 	return (1);
		// }
	// }
	// 	return (printf("minishell: cd: %s: No such file or directory\n", (*tk)->next->content), 1);