/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:45:50 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/08 15:54:24 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	redir_is_priority(t_pipex *px)
{
	t_token	*tk;

	tk = px->token;
	while (tk)
	{
		if (tk->type == REDIR_LEFT || tk->type == DELIMITER)
			return (1);
		tk = tk->next;
	}
	return (0);
}

static void	ft_exec_first_processus(t_pipex *px)
{
	char	**envp;
	char	**cmd;

	envp = env_lst_to_tab(px->ms);
	open_and_dup(px, px->token, 1);
	if (dup2(px->pipefd[1], 1) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_everything(px);
	if (!px->token->content)
		clean_exit(px->ms->exit_code, NULL);
	cmd = cmd_to_tab(px->ms, px->token);
	manage_execve(px, cmd, envp);
}

static void	ft_exec_middle_processus(t_pipex *px)
{
	char	**envp;
	char	**cmd;

	envp = env_lst_to_tab(px->ms);
	open_and_dup(px, px->token, 1);
	if (!redir_is_priority(px) && dup2(px->prev->pipefd[0], 0) == -1)
		ft_perror("dup2 failed", 1);
	if (dup2(px->pipefd[1], 1) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_everything(px);
	if (!px->token->content)
		clean_exit(px->ms->exit_code, NULL);
	cmd = cmd_to_tab(px->ms, px->token);
	manage_execve(px, cmd, envp);
}

static void	ft_exec_last_processus(t_pipex *px)
{
	char	**envp;
	char	**cmd;

	envp = env_lst_to_tab(px->ms);
	open_and_dup(px, px->token, 1);
	if (!redir_is_priority(px) && px->prev
		&& dup2(px->prev->pipefd[0], 0) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_everything(px);
	cmd = cmd_to_tab(px->ms, px->token);
	if (cmd[0])
		manage_execve(px, cmd, envp);
	wclear(0);
	clean_exit(px->ms->exit_code, NULL);
}

void	exec_sub_processus(t_pipex *px, int i)
{
	set_signals(FORK);
	if (i == px->ms->pipe_count)
		ft_exec_last_processus(px);
	else if (i == 0)
		ft_exec_first_processus(px);
	else
		ft_exec_middle_processus(px);
}
