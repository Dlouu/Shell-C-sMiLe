/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:21:41 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/09/24 15:53:55 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	move_token_to_front(t_token **to_move)
{
	t_token	*head;

	head = tk_lstfirst(*to_move);
	if ((*to_move)->prev)
		(*to_move)->prev->next = (*to_move)->next;
	else
		(*to_move)->next->prev = NULL;
	if ((*to_move)->next)
		(*to_move)->next->prev = (*to_move)->prev;
	else
		(*to_move)->prev->next = NULL;
	(*to_move)->prev = NULL;
	(*to_move)->next = head;
	(*to_move)->index = -1;
	head->prev = *to_move;
}

void	move_cmd_and_arg_to_front(t_token **tk)
{
	t_token	*temp_prev;

	while (*tk)
	{
		if ((*tk)->prev == NULL)
			break ;
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
