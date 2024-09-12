/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:05:42 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/12 17:08:12 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void add_front_pipe(t_pipex **px, t_pipex *new)
{
	if (!px || !new)
		return ;
	if (!*px)
	{
		*px = new;
		return ;
	}
	new->next = *px;
	(*px)->prev = new;
	*px = new;
}

t_pipex *pipe_add_back(t_pipex **px, t_pipex *new)
{
	t_pipex	*tmp;

	if (!px || !new)
		return (NULL);
	if (!*px)
	{
		*px = new;
		return (new);
	}
	tmp = *px;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	if (new->prev)
	{
		if (pipe(new->prev->pipefd) == -1)
			printf("pipe error\n"); //  a changer
	}
	return (new);
}

t_pipex *add_new_pipe(t_pipex *px)
{
	px = walloc(sizeof(t_pipex), 0);
	if (!px)
		return (NULL); // utile?
	px->fd_in = 0;
	px->fd_out = 0;
	px->status = 0;
	px->pipefd[0] = 0;
	px->pipefd[1] = 1;
	px->heredoc[0] = -1;
	px->heredoc[1] = -1;
	px->pid = 0;
	px->ms = NULL;
	px->next = NULL;
	px->prev = NULL;
	return (px);
}

t_pipex *setup_pipe(t_ms *ms)
{
	t_pipex *px;
	t_pipex *tmp;
	int		i;
	
	px = NULL;
	tmp = NULL;
	i = 0;
	while (i < ms->pipe_count)
	{
		tmp = add_new_pipe(tmp);
		if (!tmp)
			return (NULL);
		pipe_add_back(&px, tmp);
		i++;
	}
	return (px);
}