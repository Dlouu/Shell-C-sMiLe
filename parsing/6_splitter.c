/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_splitter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:04:25 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/23 15:22:55 by mbaumgar         ###   ########.fr       */
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
	new->expanded = tk->expanded; // a check
	new->blank_before_quote = tk->blank_before_quote; // a check
	new->blank_after_quote = tk->blank_after_quote; // a check
	tk_lstadd_here(tk, new);
	*i = 0;
}

void	word_splitter(t_token **token)
{
	t_token	**tk;
	int		i;

	tk = token;
	while (*tk)
	{
		// printf("splitter: '%s'\n", (*tk)->content); // a check
		// while ((*tk)->content[i] && ft_isblank((*tk)->content[i]))
		// 	i++;
		if ((*tk)->squote == 0 && (*tk)->dquote == 0 && (*tk)->expanded) // a check
		{
			i = 0;
			while ((*tk)->content[i]) // a check
			{
				if (!ft_isblank((*tk)->content[i]) && (*tk)->content[i + 1] && \
				ft_isblank((*tk)->content[i + 1])) // a check
					split_nodes(*tk, &i);
				i++;
			}
		}
		tk = &(*tk)->next;
	}
}

void	split_on_pipe_and_update_index(t_token **tk)
{
	t_token	*temp;
	int		index;

	index = 0;
	while ((*tk)->next && (*tk)->next->type != PIPE)
	{
		(*tk)->index = index;
		index++;
		*tk = (*tk)->next;
	}
	if ((*tk)->next && (*tk)->next->type == PIPE)
	{
		temp = (*tk)->next;
		(*tk)->next = NULL;
		(*tk)->index = index;
		*tk = temp->next;
		(*tk)->prev = NULL;
	}
	else
	{
		(*tk)->index = index;
		*tk = (*tk)->next;
	}
}

void	pipe_splitter(t_ms *ms)
{
	t_token	*tk;
	t_token	**token_splitted;
	t_token	**head;
	int		i;

	tk = ms->token_lexed;
	i = 0;
	token_splitted = walloc(sizeof(t_token *) * (ms->pipe_count + 2), FALSE);
	head = token_splitted;
	while (tk)
	{
		token_splitted[i] = tk;
		split_on_pipe_and_update_index(&tk);
		i++;
	}
	token_splitted[i] = NULL;
	ms->token = head;
}
