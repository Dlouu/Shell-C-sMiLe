/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:14 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/09/21 23:58:21 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	al_lstadd(t_alloc **al_lst, t_alloc *new)
{
	new->next = *al_lst;
	*al_lst = new;
}

int	al_lstdelone(t_alloc **al_lst_head, t_alloc *al_to_del)
{
	t_alloc	*temp;
	t_alloc	*next;
	t_alloc	*prev;

	prev = *al_lst_head;
	temp = *al_lst_head;
	next = temp->next;
	while (temp)
	{
		if (temp == al_to_del)
		{
			if (temp == *al_lst_head)
				*al_lst_head = next;
			next = temp->next;
			prev->next = next;
			free(temp->ptr);
			free(temp);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

void	al_lstclear(t_alloc **al_lst, int free_critical)
{
	t_alloc	*temp;
	t_alloc	*next;

	if (!*al_lst)
		return ;
	temp = *al_lst;
	while (temp)
	{
		next = temp->next;
		if ((temp->critical == TRUE && free_critical) || \
			temp->critical == FALSE)
		{
			if (temp == *al_lst)
				*al_lst = next;
			al_lstdelone(al_lst, temp);
		}
		temp = next;
	}
}

t_alloc	*al_lstnew(void *content, int critical)
{
	t_alloc	*new;

	if (!content)
		return (NULL);
	new = (t_alloc *)malloc(sizeof(t_alloc));
	if (!new)
		return (NULL);
	new->ptr = content;
	new->critical = critical;
	new->next = NULL;
	return (new);
}
