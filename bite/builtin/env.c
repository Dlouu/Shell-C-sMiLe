/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:09 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 18:06:55 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_ms *ms)
{
	t_list	*temp;

	temp = ms->env;
	while (temp)
	{
		if (((t_env *)temp->data)->value != NULL)
		{
			ft_putstr_fd(((t_env *)temp->data)->key,
				get_fds(ms, STDOUT_FILENO));
			ft_putstr_fd("=", get_fds(ms, STDOUT_FILENO));
			ft_putendl_fd(((t_env *)temp->data)->value,
				get_fds(ms, STDOUT_FILENO));
		}
		temp = temp->next;
	}
	return (0);
}
