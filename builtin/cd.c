/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/27 16:46:55 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	file_not_found_or_permission_denied(t_token *tk)
{
	if (errno == 13)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(tk->next->content, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(tk->next->content, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
}

int	ft_cd(t_ms *ms, t_token *tk)
{
	char	*old_path;
	char	*new_path;

	old_path = getcwd(NULL, 0);
	ms->exit_code = 1;
	if (tk->next && tk->next->type == ARG && \
	tk->next->next && tk->next->next->type == ARG)
		return (ft_putendl_fd("minishell: cd: too many arguments", \
		STDERR_FILENO), ms->exit_code);
	if (!tk->next || ft_strcmp(tk->next->content, "~") == 0)
	{
		if (chdir(find_env_value(ms->env, "HOME")) == -1)
			return (ft_putendl_fd("cd: HOME not set", \
			STDERR_FILENO), ms->exit_code);
	}
	else if (chdir(tk->next->content) == -1)
		return (file_not_found_or_permission_denied(tk), ms->exit_code);
	replace_env_value(ms->env, "OLDPWD", old_path);
	new_path = getcwd(NULL, 0);
	replace_env_value(ms->env, "PWD", new_path);
	ms->exit_code = 0;
	return (ms->exit_code);
}
