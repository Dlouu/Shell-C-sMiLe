/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:29:45 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/02 22:10:41 by mbaumgar         ###   ########.fr       */
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

void	ft_close_fds_builtins(t_pipex *px)
{
	int	fds[2];

	fds[0] = get_fds(px->ms, STDIN_FILENO);
	fds[1] = get_fds(px->ms, STDOUT_FILENO);
	if (fds[0] != STDIN_FILENO && fds[0] != -1)
		close(fds[0]);
	if (fds[1] != STDOUT_FILENO && fds[1] != -1)
		close(fds[1]);
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
