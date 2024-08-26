/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_recombiner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:48:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/26 14:18:36 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int		temp_type;

	temp_type = tk->type;
	next = tk->next;
	new_content = ft_strjoin(tk->content, next->content, FALSE);
	tk->content = new_content;
	tk->next = next->next;
	if (next->next)
		next->next->prev = tk;
	tk->type = next->type;
}

// void	split_expanded_var(t_token *tk)
// {
// 	t_token	*prev;
// 	char	*new_content;

// 	prev = tk->prev;
// 	new_content = ft_strjoin(prev->content, tk->content, FALSE);
// 	prev->content = new_content;
// 	prev->next = tk->next;
// 	if (tk->next)
// 		tk->next->prev = prev;
// }

void	recombiner(t_token *tk)
{
	while (tk)
	{
		if (tk->next && (tk->next->type < 3) && (tk->type < 3) \
		&& tk->blank_after_quote == 0 && tk->next->blank_before_quote == 0 \
		&& tk->expanded == 0) // a check
			recombine_next_token(tk);
		if (tk->prev && (tk->prev->type < 3) && (tk->type < 3) \
		&& tk->prev->blank_after_quote == 0 && tk->blank_before_quote == 0 \
		&& tk->expanded == 0) // a check
			recombine_prev_token(tk);
		tk = tk->next;
	}
}
