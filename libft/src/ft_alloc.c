/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:04:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/03 17:15:46 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*new_alloc(t_alloc *allocs, int size, int critical)
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
	al_lstadd_back(allocs, lst_allocs);
	return (new_malloc);
}

void	clear_alloc(t_list *allocs, int free_critical)
{
	t_alloc	*tmp;

	while (allocs)
	{
		tmp = allocs;
		if (free_critical || !tmp->critical)
			free(tmp->ptr);
		free(tmp);
		allocs = allocs->next;
	}
}

void	free_alloc(void *allocs)
{
	t_alloc	*tmp;

	while (allocs)
	{
		tmp = allocs;
		if (tmp->ptr == allocs)
		{
			al_lstdelone(allocs, tmp);
			// free(tmp->ptr);
			// free(tmp);
			return ;
		}
		allocs = tmp->next;
	}
}

int	size_alloc(t_alloc *lst_allocs)
{
	int		size;

	size = 0;
	while (lst_allocs)
	{
		size++;
		lst_allocs = lst_allocs->next;
	}
	return (size);
}

void	allocator(int size, t_alloc_code code, void *ptr, int critical)
{
	static t_list	*lst_allocs;

	if (code == ALLOC)
		return (new_alloc(&lst_allocs, size, critical));
	else if (code == CLEAR)
		return (clear_alloc(&lst_allocs, critical));
	else if (code == FREE)
		return (free_alloc(ptr));
	else if (code == SIZE)
		return (size_alloc(&lst_allocs));
}
