/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:20 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 20:02:02 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	del_env_node(t_list **env, char *key)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			wfree(((t_env *)tmp->content)->key);
			wfree(((t_env *)tmp->content)->value);
			wfree(tmp->content);
			wfree(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_ms *ms)
{
	return (ms->exit_code);
}
