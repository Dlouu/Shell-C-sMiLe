/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:05:42 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/17 16:53:23 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void add_back_pipe(t_pipex **px, t_pipex *new)
{
	t_pipex	*tmp;

	if (!new)
		return ;
	if (!*px)
	{
		*px = new;
		return ;
	}
	tmp = *px;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	if (new->prev)
		if (pipe(new->prev->pipefd) == -1)
			return ; // erreur
}

static t_pipex	*add_new_pipe(t_ms *ms)
{
	t_pipex	*new;

	(void)ms;
	new = walloc(sizeof(t_pipex), TRUE);
	if (!new)
		return (NULL);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->status = 0;
	new->pipefd[0] = -1;
	new->pipefd[1] = -1;
	new->heredoc[0] = -1;
	new->heredoc[1] = -1;
	new->pid = 0;
	new->ms = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_pipex *setup_pipe(t_ms *ms)
{
	t_pipex	*px;
	t_pipex	*tmp;
	int 	i;

	i = 0;
	px = add_new_pipe(ms);
	tmp = px;
	while (i < ms->pipe_count)
	{
		add_back_pipe(&px, add_new_pipe(ms));
		i++;
	}
	return (tmp);
}
