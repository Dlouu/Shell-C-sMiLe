/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:45:50 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/02 18:05:33 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unlink_ptr_for_execve(char *path, char **cmd, char **envp)
{
	int	i;

	i = -1;
	wunlink(path);
	while (cmd && cmd[++i])
		wunlink(cmd[i]);
	wunlink(cmd);
	i = -1;
	while (envp && envp[++i])
		wunlink(envp[i]);
	wunlink(envp);
}

static void	manage_execve(t_pipex *px, char **cmd, char **envp)
{
	char	*cmd_path;

	if (px->token->type == BUILTIN)
		find_builtin(px, px->token);
	cmd_path = find_path(cmd[0], envp, px->ms);
	if ((!cmd_path || (!px->token->content[0] && !px->token->expanded)) && \
	cmd[0])
		return (ft_error(cmd[0], "command not found", 1, 1));
	if (!px->token->content[0] && px->token->expanded == 2)
		clean_exit(0);
	unlink_ptr_for_execve(cmd_path, cmd, envp);
	wclear(1);
	if (cmd)
	{
		if (execve(cmd_path, cmd, envp) == -1)
			ft_perror("execve error", 1);
	}
}

static void	ft_exec_first_processus(t_pipex *px)
{
	char	**envp;
	char	**cmd;

	envp = env_lst_to_tab(px->ms);
	open_and_dup(px, px->token, 1);
	if (dup2(px->pipefd[1], 1) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_fds(px);
	ft_close_pipe(px->heredoc);
	if (!px->token->content)
		clean_exit(px->ms->exit_code);
	cmd = cmd_to_tab(px->ms, px->token);
	manage_execve(px, cmd, envp);
}

static void	ft_exec_middle_processus(t_pipex *px)
{
	char	**envp;
	char	**cmd;

	envp = env_lst_to_tab(px->ms);
	open_and_dup(px, px->token, 1);
	if (px->heredoc[0] == -1 && dup2(px->prev->pipefd[0], 0) == -1)
		ft_perror("dup2 failed", 1);
	if (dup2(px->pipefd[1], 1) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_fds(px);
	ft_close_pipe(px->heredoc);
	if (!px->token->content)
		clean_exit(px->ms->exit_code);
	cmd = cmd_to_tab(px->ms, px->token);
	manage_execve(px, cmd, envp);
}

static void	ft_exec_last_processus(t_pipex *px)
{
	char	**envp;
	char	**cmd;

	envp = env_lst_to_tab(px->ms);
	open_and_dup(px, px->token, 1);
	if (px->prev && dup2(px->prev->pipefd[0], 0) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_fds(px);
	ft_close_pipe(px->heredoc);
	cmd = cmd_to_tab(px->ms, px->token);
	if (cmd[0])
		manage_execve(px, cmd, envp);
	wclear(0); // sinon leak mais a verifier si ok
	clean_exit(px->ms->exit_code); // ^^
}

void	exec_sub_processus(t_pipex *px, int i)
{
	if (i == px->ms->pipe_count)
		ft_exec_last_processus(px);
	else if (i == 0)
		ft_exec_first_processus(px);
	else
		ft_exec_middle_processus(px);
}
