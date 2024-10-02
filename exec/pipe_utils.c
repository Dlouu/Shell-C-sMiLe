/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:05:42 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/02 15:24:48 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_fds(t_ms *ms, int fd)
{
	if (fd == 0)
	{
		if (!ms)
			return (0);
		if (ms->fds_builtins[0] == -1)
			return (0);
		return (ms->fds_builtins[0]);
	}
	else if (fd == 1)
	{
		if (!ms)
			return (1);
		if (ms->fds_builtins[1] == -1)
			return (1);
		return (ms->fds_builtins[1]);
	}
	return (-1);
}

void	ft_close_pipe(int *pipe)
{
	if (pipe[0] != -1)
		close(pipe[0]);
	if (pipe[1] != -1)
		close(pipe[1]);
}

void	ft_close_fds(t_pipex *px)
{
	if (!px)
		return ;
	while (px->prev)
		px = px->prev;
	while (px)
	{
		if (px->pipefd[0] != 0 && px->pipefd[0] != -1)
			close(px->pipefd[0]);
		if (px->pipefd[1] != 1 && px->pipefd[1] != -1)
			close(px->pipefd[1]);
		px = px->next;
	}
}

static void	add_back_pipe(t_pipex **px, t_pipex *new)
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
			return ;
}

static t_pipex	*add_new_pipe(t_ms *ms, t_token *token)
{
	t_pipex	*new;

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
	new->pid = -1;
	new->ms = ms;
	new->token = token;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_pipex	*setup_pipe(t_ms *ms)
{
	t_pipex	*px;
	int		i;

	i = -1;
	px = NULL;
	while (++i <= ms->pipe_count)
		add_back_pipe(&px, add_new_pipe(ms, ms->token[i]));
	return (px);
}
