/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:14 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/04 11:07:40 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	al_lstadd(t_alloc **al_lst, t_alloc *new)
{
	if (!*al_lst || !new)
		return ;
	new->next = *al_lst;
	*al_lst = new;
}

int	al_lstdelone(t_alloc **al_lst_head, t_alloc *al_to_del)
{
	t_alloc	*temp;
	t_alloc	*next;

	temp = *al_lst_head;
	next = NULL;
	while (temp)
	{
		if (temp == al_to_del)
		{
			free(temp->ptr);	// ou wfree ?
			free(temp);			// ou wfree ?
			temp = temp->next;
			return (1);
		}
		else
			temp = temp->next;
	}
	return (0);
}

void	al_lstclear(t_alloc **al_lst, int free_critical)
{
	t_alloc	*temp;
	t_alloc	*temp_next;

	if (!*al_lst)
		return ;
	while (temp)
	{
		if (temp->critical == TRUE && free_critical == 1 || \
			temp->critical == FALSE)
		{
			temp->next = temp_next;
			wfree(temp->ptr);
			wfree(temp);
		}
		temp = temp_next;
		*al_lst = temp;
	}
	al_lst = NULL;
}

t_alloc	*al_lstnew(void *content, int critical)
{
	t_alloc	*new;

	new = (t_alloc *)malloc(sizeof(t_alloc));
	if (!new)
		return (NULL);
	new->ptr = content;
	new->critical = critical;
	new->next = NULL;
	return (new);
}
