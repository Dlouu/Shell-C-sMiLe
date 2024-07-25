/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:24:42 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/25 05:24:48 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*tk_lstnew(char *content)
{
	t_token	*new;

	new = walloc(sizeof(t_token), FALSE);
	new->content = ft_strdup(content, FALSE);
	new->type = -1;
	new->index = -1;
	new->builtin = -1;
	new->blank_after_quote = -1;
	new->squote = -1;
	new->dquote = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	tk_lstadd(t_token **tk_lst, t_token *new)
{
	t_token	*temp;

	if (!new)
		return ;
	if (!*tk_lst)
	{
		*tk_lst = new;
		new->index = 0;
	}
	else
	{
		temp = *tk_lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
		new->index = new->prev->index + 1;
	}
}

void	tk_lstclear(t_token **tk_lst)
{
	t_token	*temp;

	if (!tk_lst)
		return ;
	while (*tk_lst)
	{
		temp = (*tk_lst)->next;
		wfree((*tk_lst)->content);
		wfree(*tk_lst);
		*tk_lst = temp;
	}
}

void	tk_lstprint(t_ms *ms, t_token **tk_lst)
{
	int			i;
	t_token		*tk;

	i = 0;
	while (i <= ms->pipe_count)
	{
		tk = tk_lst[i];
		while (tk)
		{
			printf("lst #%d-index%d %s   [type:%d '%d' \"%d\" blank%d]\n", \
			i, tk->index, tk->content, tk->type, \
			tk->squote, tk->dquote, tk->blank_after_quote);
			tk = tk->next;
		}
		i++;
	}
}
