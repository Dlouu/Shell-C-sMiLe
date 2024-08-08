/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_recombiner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:48:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/08 17:49:36 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	split_nodes(t_token *tk, int *i)
{
	t_token	*new;
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - *i;
	while (tk->content[*i] && !ft_isblank(tk->content[*i]))
		*i += 1;
	left = ft_substr(tk->content, 0, *i, FALSE);
	right = ft_substr(tk->content, *i + 1, len - 1, FALSE);
	tk->content = left;
	new = tk_lstnew(right);
	new->squote = tk->squote;
	new->dquote = tk->dquote;
	new->blank_before_quote = 0;
	new->blank_after_quote = 0;
	tk_lstadd_here(&tk, tk, new);
	*i = 0;
}

void	word_splitter(t_token **token)
{
	t_token	**tk;
	int		i;

	tk = token;
	while (*tk)
	{
		if ((*tk)->squote == 0 && (*tk)->dquote == 0 && (*tk)->expanded)
		{
			i = 0;
			while ((*tk)->content[i])
			{
				if (ft_isblank((*tk)->content[i]))
					split_nodes(*tk, &i);
				i++;
			}
		}
		tk = &(*tk)->next;
	}
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
		if (tk->prev && (tk->squote || tk->dquote) && \
			tk->blank_before_quote == 0)
			recombine_prev_token(tk);
		tk = tk->next;
	}
}
