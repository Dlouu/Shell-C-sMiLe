/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_warper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:04:50 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/04 12:31:55 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*walloc(int size, int critical)
{
	return (ft_allocator(size, ALLOC, NULL, critical));
}

void	wclear(int free_critical)
{
	if (free_critical)
		ft_allocator(0, CLEAR, NULL, TRUE);
	else
		ft_allocator(0, CLEAR, NULL, FALSE);
}

void	wfree(void *ptr)
{
	ft_allocator(0, FREE, ptr, 0);
}
