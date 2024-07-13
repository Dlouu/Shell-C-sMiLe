/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:09 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/13 15:46:52 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
arreter d'utiliser les structures de test
utiliser t_ms pour chopper env
*/
#include "../inc/minishell.h"

int	ft_env(t_ms *ms)
{
	char *bla;

	bla = ms->env->content->key;
	while (ms->env->content)
	{
		ft_putstr_fd(((t_env *)ms->env->content)->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(((t_env *)ms->env->content)->value, 1);
		ms->env->content = ms->env->content->next;
	}
	return (0);
}
