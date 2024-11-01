/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:05:42 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/10 12:52:24 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			ft_perror("pipe error", 1);
}

static t_pipex	*add_new_pipe(t_ms *ms, t_token *token)
{
	t_pipex	*new;

	new = walloc(sizeof(t_pipex), TRUE);
	if (!new)
		return (NULL);
	new->pipefd[0] = -1;
	new->pipefd[1] = -1;
	new->heredoc[0] = -1;
	new->heredoc[1] = -1;
	new->buff = NULL;
	new->pid = -1;
	new->exec_builtin = 1;
	new->is_subprocess = 0;
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
