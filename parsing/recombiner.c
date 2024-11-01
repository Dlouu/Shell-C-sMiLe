/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recombiner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:48:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/02 19:52:41 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	recombine_prev_token(t_token *tk)
{
	t_token	*prev;
	char	*new_content;

	prev = tk->prev;
	new_content = ft_strjoin(prev->content, tk->content, FALSE);
	prev->content = new_content;
	prev->type = tk->type;
	prev->next = tk->next;
	if (tk->next)
		tk->next->prev = prev;
}

void	recombine_next_token(t_token *tk)
{
	t_token	*next;
	char	*new_content;

	next = tk->next;
	new_content = ft_strjoin(tk->content, next->content, FALSE);
	tk->content = new_content;
	tk->next = next->next;
	if (next->next)
		next->next->prev = tk;
}

void	recombiner(t_token *tk)
{
	while (tk)
	{
		if (tk->index != 0 && (tk->type < 3) && (!tk->expanded || tk->dollar) \
		&& (tk->next && (tk->next->type < 3) \
		&& !tk->blank_after && !tk->next->blank_before))
			recombine_next_token(tk);
		if ((tk->type < 3) && (!tk->expanded || tk->dollar) \
		&& (tk->prev && (tk->prev->type < 3) \
		&& !tk->prev->blank_after && !tk->blank_before))
			recombine_prev_token(tk);
		tk = tk->next;
	}
}
