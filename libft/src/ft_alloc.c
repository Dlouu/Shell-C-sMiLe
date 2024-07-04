/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:04:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/04 12:42:01 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	*new_alloc(t_alloc *allocs, int size, int critical)
{
	void	*new_malloc;
	t_alloc	*lst_allocs;

	new_malloc = malloc(size);
	if (!new_malloc)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		wclear(1);
		exit(1);
	}
	lst_allocs = al_lstnew(new_malloc, critical);
	if (!lst_allocs)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		free(new_malloc);
		wclear(1);
		exit(1);
	}
	al_lstadd(&allocs, lst_allocs);
	return (new_malloc);
}

static void	free_alloc(t_alloc **allocs)
{
	t_alloc	*temp;

	if (!*allocs)
		return ;
	while (*allocs)
	{
		temp = *allocs;
		if (temp->ptr == *allocs)
		{
			al_lstdelone(allocs, temp);
			// free(temp->ptr);
			// free(temp);
			return ;
		}
		*allocs = temp->next;
	}
}

void	*ft_allocator(int size, t_alloc_code code, void *ptr, int critical)
{
	static t_alloc	*lst_allocs;

	if (code == ALLOC)
		return (new_alloc(lst_allocs, size, critical));
	else if (code == CLEAR)
		al_lstclear(&lst_allocs, critical);
	else if (code == FREE)
		free_alloc(ptr);
	return (NULL);
}
