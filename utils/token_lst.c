/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:24:42 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/20 11:48:45 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*tk_delone(t_token **tk_lst, t_token *tk)
{
	t_token	*temp;

	if (!tk)
	{
		printf("tk is NULL\n");
		return (NULL);
	}
	printf("tk->content DELONENENENEN: %s\n", tk->content);
	if (tk == *tk_lst)
	{
		*tk_lst = tk->next;
		if (*tk_lst)
			(*tk_lst)->prev = NULL;
	}
	else
	{
		temp = tk->prev;
		temp->next = tk->next;
		if (tk->next)
			tk->next->prev = temp;
	}
	// wfree(tk->content);
	// wfree(tk);
	update_index(tk_lst);
	return (NULL);
}

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
	new->expanded = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	tk_lstadd_here(t_token **lst, t_token *here, t_token *new)
{
	t_token	*temp;

	temp = here->next;
	here->next = new;
	new->prev = here;
	new->next = temp;
	if (temp)
		temp->prev = new;
	update_index(lst);
}

void	tk_lstadd(t_token **tk_lst, t_token *new)
{
	t_token	*temp;

	if (!new)
		return ;
	printf("tk_lst dans kle add: %p\n", *tk_lst);
	if (!*tk_lst || !tk_lst)
	{
		printf("fgyhujijuhgjijhgv\n");
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
