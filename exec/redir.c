/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:32 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/30 16:55:12 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void redir_out(char *file, t_pipex *px, int redir)
{
	if (redir == REDIR_RIGHT)
	{
		px->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (px->fd_out == -1)
			return (perror("open error\n"), exit(1));
	}
	else
	{
		px->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (px->fd_out == -1)
			return (perror("open error\n"), exit(1));
	}
}

static void redir_in(char *file, t_pipex *px, int redir, t_ms *ms)
{
	if (redir == REDIR_DOUBLE_LEFT)
	{
		printf("heredoc%d\n", ms->heredoc_count);
		printf("check%d\n", ms->heredoc_count_check);
		if (ms->heredoc_count == ms->heredoc_count_check)
			return ;
		if (pipe(px->pipefd) == -1)
			return ;
		//manage_heredoc(ms, px);
	}
	else if (redir == REDIR_LEFT)
	{
		if (access(file, F_OK) == -1)
		{
			perror("File does not exist\n");
			return;
		}
		if ((px->fd_in = open(file, O_RDONLY)) == -1)
		{
			close(px->fd_in);
			perror("open error\n");
		}
	}
}

/*
az < qs < grep Music crash
*/

void init_pipe(t_pipex *px)
{
	px->save_in = 0;
	px->save_out = 0;
	px->fd_in = STDIN_FILENO;
	px->fd_out = STDOUT_FILENO;
	px->status = 0;
	px->pipefd[0] = 0;
	px->pipefd[1] = 0;
	px->pid[0] = 0;
	px->pid[1] = 0;
	px->i = 0;
}

void open_and_dup(t_pipex *px, t_token *tk, t_ms *ms)
{
	px->fd_in = STDIN_FILENO;
	px->fd_out = STDOUT_FILENO;
	px->save_in = dup(STDIN_FILENO);
	px->save_out = dup(STDOUT_FILENO);
	while (tk)
	{
		if (tk->type == REDIR_LEFT || tk->type == REDIR_DOUBLE_LEFT)
			redir_in(tk->next->content, px, tk->type, ms);
		else if (tk->type == REDIR_RIGHT || tk->type == REDIR_DOUBLE_RIGHT)
			redir_out(tk->next->content, px, tk->type);
		tk = tk->next;
	}
	if (px->fd_in != STDIN_FILENO)	
	{
		dup2(px->fd_in, STDIN_FILENO);
		close(px->fd_in);
	}
	if (px->fd_out != STDOUT_FILENO)
	{
		dup2(px->fd_out, STDOUT_FILENO);
		close(px->fd_out);
	}
}

/*
fichier = out 
fd_out = open(fichier, O_WRONLY | O_CREAT | O_TRUNC, 0644);
if fichier->next n'est pas nul
close(fd_out);
fd_out = open(fichier->next, O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd_out == STDOUT)
	dup2(fd_out, STDOUT_FILENO);
exec_command
if (fd_out != STDOUT)
	close(fd_out);
	dup2(save_out, STDOUT_FILENO);
*/
