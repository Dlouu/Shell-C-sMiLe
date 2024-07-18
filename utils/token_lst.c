/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:22:57 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/18 13:34:40 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/typedefs.h"

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
		*tk_lst = new;
	else
	{
		temp = *tk_lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
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

void	tk_lstprint(t_token *token_lst)
{
	int	i;

	i = 1;
	while (token_lst)
	{
		printf("token #%d: %s\n", i, token_lst->content);
		token_lst = token_lst->next;
		i++;
	}
}
