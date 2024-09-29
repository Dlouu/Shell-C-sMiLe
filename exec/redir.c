/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:32 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/29 21:17:33 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	verif_redir(t_pipex *px, int save_in, int save_out)
{
	if (save_in != -1)
	{
		if (dup2(save_in, 0) == -1)
			return (perror("dup2 error\n"), exit(1));
		px->pipefd[0] = save_in;
	}
	if (save_out != -1)
	{
		if (dup2(save_out, 1) == -1)
			return (perror("dup2 error\n"), exit(1));
		px->pipefd[1] = save_out;
	}
}

static void	redir_out(char *file, int redir, int *save_out)
{
	if (redir == REDIR_RIGHT)
		*save_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir == REDIR_DOUBLE_RIGHT)
		*save_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*save_out == -1)
		return (perror("open error\n"), exit(1));
}

static void	redir_in(char *file, t_pipex *px, int redir, int *save_in)
{
	if (redir == REDIR_DOUBLE_LEFT)
		manage_heredoc(px);
	else
	{
/*		if (access(file, F_OK) == -1)
		{
			perror("File does not exist\n");
			return ;
		}*/
		*save_in = open(file, O_RDONLY);
		if (*save_in == -1)
			return (perror("open error\n"), exit(1));
	}
}

void	open_and_dup(t_pipex *px, t_token *tk)
{
	int save_in;
	int save_out;

	save_in = -1;
	save_out = -1;
	while (tk)
	{
		if (tk->type == REDIR_LEFT || tk->type == REDIR_DOUBLE_LEFT)
			redir_in(tk->next->content, px, tk->type, &save_in);
		else if (tk->type == REDIR_RIGHT || tk->type == REDIR_DOUBLE_RIGHT)
			redir_out(tk->next->content, tk->type, &save_out);
		tk = tk->next;
	}
	verif_redir(px, save_in, save_out);
}
