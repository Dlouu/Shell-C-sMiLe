/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:20 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/12 17:49:21 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	del_env_node(t_list **env_lst, char *key)
{
	t_list	*current;
	t_list	*to_del;

	current = *env_lst;
	to_del = find_env_node(*env_lst, key);
	while (current)
	{
		if (current->next == to_del)
		{
			current->next = to_del->next;
			break ;
		}
		current = current->next;
	}
}

int	ft_unset(t_ms *ms)
{
	t_token	*token;

	token = *ms->token;
	if (!token->next)
	{
		ft_putstr_fd("minishell: unset: not enough arguments\n", STDERR_FILENO);
		ms->exit_code = 1;
		return (ms->exit_code);
	}
	else 
		del_env_node(&ms->env, token->next->content);
	return (ms->exit_code);
}
