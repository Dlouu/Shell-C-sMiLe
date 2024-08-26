/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:32 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/26 16:01:19 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void redir_out(t_ms *ms, t_pipex *px)
{
	t_token *tk;
	t_token *tmp;

	tk = ms->token[ms->current_pipe];
	tmp = tk->next;
	if (tmp->type == REDIR_RIGHT)
	{
		px->outfile = open(tmp->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (px->outfile < 0)
		{
			printf("File not found\n");
			exit(1);
		}
		px->fd_out = dup(STDOUT_FILENO);
		if (dup2(px->fd_out, STDOUT_FILENO) < 0)
		{
	printf("tmp->content\n");
			printf("dup2 error\n");
			exit(1);
		}
	}
	else if (tmp->type == REDIR_DOUBLE_RIGHT)
	{
		px->outfile = open(tmp->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (px->outfile < 0)
		{
			printf("File not found\n");
			exit(1);
		}
		px->fd_out = dup(STDOUT_FILENO);
		if (dup2(px->outfile, STDOUT_FILENO) < 0)
		{
			printf("dup2 error\n");
			exit(1);
		}
	}
}

static void redir_in(t_ms *ms, t_pipex *px)
{
	t_token *tk;
	t_token *tmp;

	tk = ms->token[ms->current_pipe];
	tmp = tk->next;
	if (tmp->type == REDIR_LEFT)
	{
		px->infile = open(tmp->content, O_RDONLY);
		if (px->infile < 0)
		{
			printf("File not found\n");
			exit(1);
		}
		px->fd_in = dup(STDIN_FILENO);
		if (dup2(px->infile, STDIN_FILENO) < 0)
		{
			printf("dup2 error\n");
			exit(1);
		}
	}
	else if (tmp->type == REDIR_DOUBLE_LEFT)
	{
		manage_heredoc(ms);
		px->fd_in = dup(STDIN_FILENO);
		if (dup2(px->infile, STDIN_FILENO) < 0)
		{
			printf("dup2 error\n");
			exit(1);
		}
	}
	ms->current_pipe++;
}

void init_pipe(t_pipex *px)
{
	px->infile = 0;
	px->outfile = 0;
	px->fd_in = 0;
	px->fd_out = 0;
	px->status = 0;
	px->pipefd[0] = 0;
	px->pipefd[1] = 0;
	px->pid[0] = 0;
	px->pid[1] = 0;
	px->i = 0;
}

void check_redir_nils(t_ms *ms, t_pipex *px, t_token *tk)
{
	int count;
	int i;
	px->infile = STDIN_FILENO;
	px->outfile = STDOUT_FILENO;
	px->fd_in = dup(STDIN_FILENO);
	px->fd_out = dup(STDOUT_FILENO);

	i = 0;
	count = count_redir_nils(ms);
	printf("count = %d\n", count);
	while (i < count)
	{
		if (tk->next->type == REDIR_LEFT || tk->next->type == REDIR_DOUBLE_LEFT)
			redir_in(ms, px);
		else if (tk->next->type == REDIR_RIGHT || tk->next->type == REDIR_DOUBLE_RIGHT)
			redir_out(ms, px);
		i++;
	}
}