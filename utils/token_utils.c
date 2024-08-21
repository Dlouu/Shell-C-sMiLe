/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:24:42 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/21 13:53:34 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tk_lstprint_type(t_token *tk)
{
	if (tk->type == PIPE)
		printf("   PIPE: ");
	else if (tk->type >= 3 && tk->type <= 6)
		printf("  REDIR: ");
	else if (tk->type == COMMAND)
		printf("COMMAND: ");
	else if (tk->type == BUILTIN)
		printf("BUILTIN: ");
	else if (tk->type == ARG)
		printf("    ARG: ");
	else if (tk->type == FILENAME)
		printf("   FILE: ");
	else if (tk->type == DELIMITER)
		printf("  DELIM: ");
	else
		printf("UNDEFINED");
}

void	tk_lstprint(t_ms *ms, t_token **tk_lst)
{
	int			i;
	t_token		*tk;

	i = 0;
	while (i <= ms->pipe_count)
	{
		tk = tk_lst[i];
		if (i == 0)
			printf("#%d\n", i);
		else
			printf("\n#%d\n", i);
		while (tk)
		{
			printf(" '-%d ", tk->index);
			tk_lstprint_type(tk);
			printf("[%s]           ['%d' \"%d\" blank %d-%d]\n", tk->content, \
			tk->squote, tk->dquote, tk->blank_before_quote, \
			tk->blank_after_quote);
			tk = tk->next;
		}
		i++;
	}
	printf("- - - -\n");
}

t_token	*tk_lstlast(t_token *tk)
{
	if (!tk)
		return (NULL);
	while (tk->next)
		tk = tk->next;
	return (tk);
}

t_token	*tk_lstfirst(t_token *tk)
{
	if (!tk)
		return (NULL);
	while (tk->prev)
		tk = tk->prev;
	return (tk);
}

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
