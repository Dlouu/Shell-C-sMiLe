/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:51:04 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/08 16:45:41 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	*ft_free(char **result, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		wfree(result[i]);
		i++;
	}
	wfree(result);
	return (NULL);
}

char	**ft_strdup_array(char **to_copy, int height, int critical)
{
	char	**copy;
	int		i;

	i = 0;
	if (!to_copy)
		return (NULL);
	copy = (char **)walloc(sizeof(char *) * (height), critical);
	if (!copy)
		return (NULL);
	while (height > i)
	{
		copy[i] = ft_strdup(to_copy[i], critical);
		if (!copy[i])
			return (ft_free(copy, i));
		i++;
	}
	return (copy);
}
