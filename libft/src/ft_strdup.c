/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:51:04 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/08 16:31:44 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s, int critical)
{
	char	*str;
	size_t	size;

	size = ft_strlen(s) + 1;
	str = walloc(sizeof(char) * size, critical);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, size);
	return (str);
}
