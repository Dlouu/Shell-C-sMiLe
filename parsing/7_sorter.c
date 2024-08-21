/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_sorter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:21:41 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/21 15:27:54 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	token_has_no_command(t_token *tk)
{
	while (tk)
	{
		if (tk->type == COMMAND || tk->type == BUILTIN)
			return (0);
		tk = tk->next;
	}
	return (1);
}

void	move_cmd_and_arg_to_front(t_token **tk)
{
	t_token	*temp_prev;

	while (*tk)
	{
		temp_prev = (*tk)->prev;
		if ((*tk)->index == -1 && \
		((*tk)->type == COMMAND || (*tk)->type == BUILTIN))
			break ;
		if ((*tk)->index != -1 && ((*tk)->type == ARG || \
		(*tk)->type == COMMAND || (*tk)->type == BUILTIN))
			move_token_to_front(tk);
		*tk = temp_prev;
	}
}

void	sort_token(t_ms *ms)
{
	t_token	**tk_lst;
	t_token	*tk;
	t_token	*temp;
	int		i;

	tk_lst = ms->token;
	i = 0;
	while (tk_lst[i])
	{
		tk = tk_lst[i];
		if (token_has_no_command(tk) || tk == tk_lstlast(tk))
		{
			i++;
			continue ;
		}
		tk = tk_lstlast(tk);
		temp = tk;
		move_cmd_and_arg_to_front(&tk);
		tk_lst[i] = tk_lstfirst(temp);
		i++;
	}
}
