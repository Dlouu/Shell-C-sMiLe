/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:24:42 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/06 17:38:36 by mbaumgar         ###   ########.fr       */
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
	new->blank_before_quote = -1;
	new->squote = -1;
	new->dquote = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

//a tester, à utiliser pour split apres expansion et avant pipe_splitter
void	tk_lstadd_here(t_token **tk_lst, t_token *here, t_token *new)
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
		temp = here->next;
		here->next = new;
		new->prev = here;
		new->next = temp;
		if (temp)
			temp->prev = new;
		new->index = new->prev->index + 1;
	}
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
		if (i == 0)
			printf("#%d\n", i);
		else
			printf("\n#%d\n", i);
		while (tk)
		{
			printf(" '-%d ", tk->index);
			tk_lstprint_type(tk);
			printf(": [%s]           ['%d' \"%d\" blank %d-%d]\n", tk->content, \
			tk->squote, tk->dquote, tk->blank_before_quote, \
			tk->blank_after_quote);
			tk = tk->next;
		}
		i++;
	}
	printf("- - - -\n");
}
