/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 15:54:35 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
ls -l > oui | cat < oui | echo bite > non

ls -l > infile > outfile > infile (outfile vide mais infile remplie) good

grep "login.sh" < infile > outfile (outfile recupere le grep) good

grep "Videos" < infile | cat -e > outfile good

tr a-z A-Z > first_file << oui | tr A-Z a-z > second_file << non
*/


void	find_builtin(t_pipex *px, t_token *token)
{
	open_and_dup(px, token, 0);
	if (ft_strcmp(token->content, "cd") == 0)
		ft_cd(px->ms, token);
	else if (ft_strcmp(token->content, "echo") == 0)
		ft_echo(px->ms, token);
	else if (ft_strcmp(token->content, "env") == 0)
		ft_env(px->ms);
	else if (ft_strcmp(token->content, "exit") == 0)
		ft_exit(px->ms, token);
	else if (ft_strcmp(token->content, "export") == 0)
		ft_export(px->ms, token);
	else if (ft_strcmp(token->content, "pwd") == 0)
		ft_pwd(px->ms);
	else if (ft_strcmp(token->content, "unset") == 0)
		ft_unset(px->ms, token);
	ft_close_fds_builtins(px->ms);
	if (px->pid == 0)
		clean_exit(px->ms->exit_code, NULL);
}

void	manage_execve(t_pipex *px, char **cmd, char **envp)
{
	char	*cmd_path;

	if (px->token->type == BUILTIN)
		find_builtin(px, px->token);
	if (!find_my_token(px, COMMAND) && !find_my_token(px, BUILTIN))
		clean_exit(0, NULL);
	cmd_path = find_path(cmd[0], envp, px->ms);
	if ((!cmd_path || (!px->token->content[0] && !px->token->expanded)) && \
	cmd[0])
		return (ft_error(cmd[0], "command not found", 1, 127));
	if (!px->token->content[0] && px->token->expanded == 2)
		clean_exit(0, NULL);
	if (execve(cmd_path, cmd, envp) == -1)
		ft_perror("execve error", 1);
}

void	ft_exec(t_pipex *px)
{
	t_pipex	*tmp;
	int		i;

	if (px->ms->pipe_count == 0 && px->token->type == BUILTIN && !px->next)
		return (find_builtin(px, px->token));
	tmp = px;
	i = 0;
	while (px && px->token)
	{
		set_signals(FORK);
		px->pid = fork();
		if (px->pid == -1)
			ft_perror("Fork creation failed", 1);
		if (px->pid == 0)
			exec_sub_processus(px, i);
		i++;
		px = px->next;
	}
	ft_close_everything(tmp);
}

int	exec_main(t_ms *ms)
{
	t_pipex	*px;
	t_pipex	*tmp;
	int		status;

	status = 0;
	px = setup_pipe(ms);
	init_heredoc(px);
	tmp = px;
	ft_exec(px);
	printf("dans exec main avant waitpid: %d\n", ms->exit_code);
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
	printf("dans exec main apres waitpid: %d\n", ms->exit_code);
	if (g_signal == SIGQUIT)
		ft_putendl_fd("^\\Quit", STDERR_FILENO);
	g_signal = 0;
	printf("dans exec main avant wifexited: %d\n", ms->exit_code);
	if (WIFEXITED(status) && ms->dont_touch == 0)
	{
		ms->exit_code = WEXITSTATUS(status);
		printf("dans exec main wifexited: %d\n", ms->exit_code);
	}
	else if (WIFSIGNALED(status) && !(ms->dont_touch))
	{
		ms->exit_code = WTERMSIG(status) + 128;
		printf("dans exec main wifsignaled: %d\n", ms->exit_code);
	}
	return (ms->exit_code);
}
