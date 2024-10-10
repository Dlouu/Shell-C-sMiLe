/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:04:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/02 17:24:42 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	unlink_alloc(t_alloc **allocs, void *ptr)
{
	t_alloc	*temp;
	t_alloc	*prev;

	prev = NULL;
	if (!*allocs)
		return ;
	temp = *allocs;
	while (temp)
	{
		if (ptr == temp->ptr)
		{
			if (temp->next && prev)
				prev->next = temp->next;
			else
				*allocs = temp->next;
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
}

static void	*new_alloc(t_alloc **allocs, int size, int critical)
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
	al_lstadd(allocs, lst_allocs);
	return (new_malloc);
}

static void	free_alloc(t_alloc **allocs, void *ptr)
{
	t_alloc	*temp;
	t_alloc	*next;

	if (!*allocs)
		return ;
	temp = *allocs;
	while (temp)
	{
		next = temp->next;
		if (ptr == temp->ptr)
		{
			al_lstdelone(allocs, temp);
			temp = next;
			return ;
		}
		temp = next;
	}
}

void	*ft_allocator(int size, t_alloc_code code, void *ptr, int critical)
{
	static t_alloc	*lst_allocs;

	if (code == ALLOC)
		return (new_alloc(&lst_allocs, size, critical));
	else if (code == CLEAR)
		al_lstclear(&lst_allocs, critical);
	else if (code == FREE)
		free_alloc(&lst_allocs, ptr);
	else if (code == UNLINK)
		unlink_alloc(&lst_allocs, ptr);
	return (NULL);
}
