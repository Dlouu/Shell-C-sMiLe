/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:32 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/25 18:28:11 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	verif_redir(t_pipex *px)
{
	if (px->fd_in != -1)
	{
		if (dup2(px->fd_in, STDIN_FILENO) == -1)
			return (perror("dup2 failed\n"), exit(1));
		px->pipefd[0] = px->fd_in;
	}
	if (px->fd_out != -1)
	{
		if (dup2(px->fd_out, STDOUT_FILENO) == -1)
			return (perror("dup2 failed\n"), exit(1));
		px->pipefd[1] = px->fd_out;
	}
}

static void	redir_out(char *file, t_pipex *px, int redir)
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

static void	redir_in(char *file, t_pipex *px, int redir)
{
	if (redir == REDIR_DOUBLE_LEFT)
	{
		if (pipe(px->pipefd) == -1)
			return ;
		manage_heredoc(px);
	}
	else
	{
		if (access(file, F_OK) == -1)
		{
			perror("File does not exist\n");
			return ;
		}
		px->fd_in = open(file, O_RDONLY);
		if (px->fd_in == -1)
			return (perror("open error\n"), exit(1));
	}
}

void	open_and_dup(t_pipex *px, t_token *tk)
{
	while (tk)
	{
		if (tk->type == REDIR_LEFT || tk->type == REDIR_DOUBLE_LEFT)
			redir_in(tk->next->content, px, tk->type);
		else if (tk->type == REDIR_RIGHT || tk->type == REDIR_DOUBLE_RIGHT)
			redir_out(tk->next->content, px, tk->type);
		tk = tk->next;
	}
	verif_redir(px);
}
