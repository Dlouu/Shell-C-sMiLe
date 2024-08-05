/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:09 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/05 17:24:15 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_ms *ms)
{
	t_list	*temp;

	temp = ms->env;
	while (temp)
	{
		if (((t_env *)temp->data)->value[0] != 26)
		{
			ft_putstr_fd(((t_env *)temp->data)->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(((t_env *)temp->data)->value, 1);
		}
		temp = temp->next;
	}
	return (0);
}
