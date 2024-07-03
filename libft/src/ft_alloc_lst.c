/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:14 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/03 17:15:42 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

// t_alloc	*find_alloc_ptr(t_alloc *allocs, void *ptr)
// {
// 	t_alloc	*tmp;

// 	tmp = allocs;
// 	while (tmp)
// 	{
// 		if (tmp->ptr == ptr)
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

int	al_lstdelone(t_alloc *lst, void *ptr)
{
	t_alloc	*tmp;
	t_alloc	*prev;

	tmp = lst;
	prev = NULL;
	while (tmp)
	{
		if (tmp->ptr == ptr)
		{
			if (prev)
				prev->next = tmp->next;
			else
				lst = tmp->next;
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

t_alloc	*al_lstlast(t_alloc *lst)
{
	t_alloc	*tmp;

	tmp = lst;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	al_lstadd_back(t_alloc **alst, t_alloc *new)
{
	t_alloc	*tmp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = al_lstlast(*alst);
	tmp->next = new;
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
