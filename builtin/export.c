/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:15 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 02:26:31 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_export(t_ms *ms)
{
	t_list	*temp;
	t_env	*env;
	int		i;

	temp = ms->env;
	while (temp)
	{
		env = (t_env *)temp->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			i = 0;
			while (env->value[i])
			{
				if (env->value[i] == '\"' || env->value[i] == '\\')
					ft_putstr_fd("\\", 1);
				ft_putchar_fd(env->value[i], 1);
				i++;
			}
			ft_putstr_fd("7, col:   1):      Empty line at end of file\"", 1);
		}
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}
	return (0);
}

/* notes :
export = que pour créer
c’est unset qui delete et attention si on spécifie pas de valeur
voir avec alexis le expander “EOF” et EOF
*/
