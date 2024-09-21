/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:32 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/24 16:01:00 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void redir_out(char *file, t_pipex *px, int redir)
{
	if (redir == REDIR_RIGHT)
	{
		px->pipefd[1] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (px->pipefd[1] == -1)
			return (perror("open error\n"), exit(1));
	}
	else
	{
		px->pipefd[1] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (px->pipefd[1] == -1)
			return (perror("open error\n"), exit(1));
	}
}

static void redir_in(char *file, t_pipex *px)
{
/*	if (redir == REDIR_DOUBLE_LEFT)
	{
		printf("heredoc%d\n", ms->heredoc_count);
		printf("check%d\n", ms->heredoc_count_check);
		if (ms->heredoc_count == ms->heredoc_count_check)
			return ;
		if (pipe(px->pipefd) == -1)
			return ;
		//manage_heredoc(ms, px);
	}
	else */
	if (access(file, F_OK) == -1)
	{
		perror("File does not exist\n");
		return;
	}
	if ((px->pipefd[0] = open(file, O_RDONLY)) == -1)
	{
		printf("TU PASSES PAR LA\n");
		close(px->pipefd[0]);
		perror("open error\n");
	}
}

void open_and_dup(t_pipex *px, t_token *tk, t_ms *ms)
{
	if (ms->heredoc_count)
	{
		if (pipe(px->heredoc) == -1)
			return ;
		manage_heredoc(ms, px);
	}
	while (tk)
	{
		if (tk->type == REDIR_LEFT)
			redir_in(tk->next->content, px);
		else if (tk->type == REDIR_RIGHT || tk->type == REDIR_DOUBLE_RIGHT)
			redir_out(tk->next->content, px, tk->type);
		tk = tk->next;
	}
/*	if (px->fd_in != STDIN_FILENO)
	{
		if (dup2(px->fd_in, STDIN_FILENO) == -1)
			return (perror("dup2 failed\n"), exit(1));
		printf("TU PASSES PAR LA\n");
		close(px->fd_in);
	}
	if (px->fd_out != STDOUT_FILENO)
	{
		if (dup2(px->fd_out, STDOUT_FILENO) == -1)
			return (perror("dup2 failed\n"), exit(1));
		printf("TU PASSES PAR LA\n");
		close(px->fd_out);
	}*/
}
