/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:09 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 02:27:37 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
arreter d'utiliser les structures de test
utiliser t_ms pour chopper env
*/
#include "../inc/minishell.h"

int	ft_env(t_ms *ms)
{
	t_list	*temp;

	temp = ms->env;
	while (temp)
	{
		ft_putstr_fd(((t_env *)temp->data)->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(((t_env *)temp->data)->value, 1);
		temp = temp->next;
	}
	return (0);
}
