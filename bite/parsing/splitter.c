/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:04:25 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/02 18:58:06 by mbaumgar         ###   ########.fr       */
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
	new->expanded = tk->expanded;
	new->blank_before = tk->blank_before;
	new->blank_after = tk->blank_after;
	tk_lstadd_here(tk, new);
	*i = 0;
}

static void	trim_blanks(t_ms *ms, t_token *tk)
{
	if (!tk)
		return ;
	while (tk)
	{
		if (tk->expanded && tk->content[0] && ft_isblank(tk->content[0]))
			tk->content = ft_strtrim(tk->content, " ", FALSE);
		tk = tk->next;
	}
	tk = ms->token_lexed;
	while (tk)
	{
		if (tk->expanded == 1 && !tk->content[0])
			tk = tk_delone(&ms->token_lexed, tk);
		else
			tk = tk->next;
	}
	if (tk_lstlast(ms->token_lexed)->content[0] == 0)
	{
		if (ms->token_lexed->prev)
			tk_delone(&ms->token_lexed, tk_lstlast(ms->token_lexed));
	}
}

void	word_splitter(t_ms *ms, int i)
{
	t_token	*tk;

	tk = ms->token_lexed;
	if (!tk)
		return ;
	while (tk)
	{
		if (tk->squote == 0 && tk->dquote == 0 && tk->expanded)
		{
			i = 0;
			while (tk->content[i])
			{
				while (tk->content[i] && ft_isblank(tk->content[i]) \
				&& tk->content[i + 1])
					i++;
				if ((tk->content[i] && (!ft_isblank(tk->content[i]) \
				&& tk->content[i + 1]) && ft_isblank(tk->content[i + 1])) \
				|| ft_isblank(tk->content[i]))
					split_nodes(tk, &i);
				i++;
			}
		}
		tk = tk->next;
	}
	trim_blanks(ms, ms->token_lexed);
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
