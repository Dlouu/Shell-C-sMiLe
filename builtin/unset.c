/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:20 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 11:13:21 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	del_env_node(t_list **env_lst, char *key)
{
	t_list	*current;
	t_list	*to_del;

	current = *env_lst;
	to_del = find_env_node(*env_lst, key);
	while (to_del && current)
	{
		if (current->next == to_del)
		{
			current->next = to_del->next;
			wfree(((t_env *)to_del->data)->key);
			wfree(((t_env *)to_del->data)->value);
			break ;
		}
		current = current->next;
	}
}

int	ft_unset(t_ms *ms, t_token *token)
{
	if (token && !token->next)
	{
		ft_putstr_fd("minishell: unset: not enough arguments\n", STDERR_FILENO);
		ms->exit_code = 1;
		return (ms->exit_code);
	}
	else
		del_env_node(&ms->env, token->next->content);
	return (ms->exit_code);
}
