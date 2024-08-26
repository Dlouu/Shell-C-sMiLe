/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:32 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/26 15:09:29 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/* static void redir_in(t_ms *ms, t_pipex *px)
{
	
} */

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

/* void check_redir_nils(t_ms *ms, t_pipex *px, t_token *tk)
{
	int count;
	int i;

	i = 0;
	count = count_redir(ms);
	while (i < count)
	{
		if (tk->type == REDIR_LEFT || tk->type == REDIR_DOUBLE_LEFT)
			redir_in(ms, px);
		else if (tk->type == REDIR_RIGHT || tk->type == REDIR_DOUBLE_RIGHT)
			redir_out(ms, px);
		i++;
	}
} */