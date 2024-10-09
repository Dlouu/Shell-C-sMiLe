/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 21:18:32 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	file_not_found_or_permission_denied(t_token *tk, t_ms *ms)
{
	if (access(tk->next->content, R_OK) == -1)
	{
		ms->exit_code = 1;
		ms->dont_touch = 1;
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(tk->next->content, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	else
	{
		ms->exit_code = 1;
		ms->dont_touch = 1;
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(tk->next->content, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
}

static int	handle_unset_pwd(t_ms *ms)
{
	char	*temp;

	if (!find_env_node(ms->env, "OLDPWD"))
	{
		add_env_node(ms, "OLDPWD=/");
		replace_env_value(ms->env, "OLDPWD", "");
	}
	if (!find_env_node(ms->env, "PWD"))
	{
		temp = getcwd(NULL, 0);
		ms->new_path = ft_strdup(temp, FALSE);
		free(temp);
		add_env_node(ms, "PWD=/");
		replace_env_value(ms->env, "PWD", ms->new_path);
		ms->exit_code = 0;
		del_env_node(&ms->env, "OLDPWD");
		add_env_node(ms, "OLDPWD=/");
		replace_env_value(ms->env, "OLDPWD", "");
		return (0);
	}
	return (1);
}

static void	ft_update_pwds(t_ms *ms)
{
	char	*temp;

	replace_env_value(ms->env, "OLDPWD", ms->old_path);
	temp = getcwd(NULL, 0);
	ms->new_path = ft_strdup(temp, FALSE);
	free(temp);
	replace_env_value(ms->env, "PWD", ms->new_path);
}

int	ft_cd(t_ms *ms, t_token *tk)
{
	char	*temp;
	int		update_pwds;

	update_pwds = 1;
	if (handle_unset_pwd(ms))
		update_pwds = 0;
	temp = getcwd(NULL, 0);
	ms->old_path = ft_strdup(temp, FALSE);
	free(temp);
	if (tk->next && tk->next->type == ARG && \
	tk->next->next && tk->next->next->type == ARG)
		return (ft_error_no_exit("cd", "too many arguments", ms, 1), 1);
	if (!tk->next || ft_strcmp(tk->next->content, "~") == 0)
	{
		if (!find_env_node(ms->env, "HOME"))
			return (ft_error_no_exit("cd", "HOME not set", ms, 1), 1);
		else
			chdir(find_env_value(ms->env, "HOME"));
	}
	else if (chdir(tk->next->content) == -1)
		return (file_not_found_or_permission_denied(tk, ms), ms->exit_code);
	if (!update_pwds)
		ft_update_pwds(ms);
	ms->exit_code = 0;
	return (ms->exit_code);
}
