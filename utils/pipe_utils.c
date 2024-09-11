/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:05:42 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/11 18:08:32 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipex *setup_pipe(t_pipex *px)
{
	px = walloc(sizeof(t_pipex), 0);
	if (!px)
		return (NULL);
	px->fd_in = 0;
	px->fd_out = 0;
	px->status = 0;
	px->pipefd[0] = 0;
	px->pipefd[1] = 0;
	px->pid = 0;
	px->ms = NULL;
	px->next = NULL;
	px->prev = NULL;
	return (px);
}