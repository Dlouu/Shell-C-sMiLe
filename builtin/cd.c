/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/10 12:02:59 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	file_not_found_or_permission_denied(t_token *tk, t_ms *ms)
{
	if (access(tk->next->content, F_OK) == 0 && \
		access(tk->next->content, R_OK) == -1)
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

void	handle_cd_home(t_ms *ms, char *content)
{
	if (!content)
	{
		if (!find_env_node(ms->env, "HOME"))
			ft_error_no_exit("cd", "HOME not set", ms, 1);
		else
			chdir(find_env_value(ms->env, "HOME"));
	}
	else if (content && content[0] == '~')
	{
		if (!find_env_node(ms->env, "HOME"))
			chdir(ms->home);
		else
			chdir(find_env_value(ms->env, "HOME"));
	}
}

int	ft_cd(t_ms *ms, t_token *tk)
{
	char	*temp;
	int		update_oldpwd;

	update_oldpwd = 1;
	if (handle_unset_pwd(ms))
		update_oldpwd = 0;
	temp = getcwd(NULL, 0);
	ms->old_path = ft_strdup(temp, FALSE);
	if (tk->next && tk->next->type == ARG && \
	tk->next->next && tk->next->next->type == ARG)
		return (ft_error_no_exit("cd", "too many arguments", ms, 1), 1);
	if (!tk->next)
		handle_cd_home(ms, NULL);
	else if (ft_strcmp(tk->next->content, "~") == 0)
		handle_cd_home(ms, "~");
	else if (chdir(tk->next->content) == -1)
		return (file_not_found_or_permission_denied(tk, ms), ms->exit_code);
	if (!update_oldpwd)
		replace_env_value(ms->env, "OLDPWD", ms->old_path);
	temp = getcwd(NULL, 0);
	ms->new_path = ft_strdup(temp, FALSE);
	free(temp);
	replace_env_value(ms->env, "PWD", ms->new_path);
	ms->exit_code = 0;
	return (ms->exit_code);
}
