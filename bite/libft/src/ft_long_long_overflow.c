/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_long_overflow.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:05:32 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/10 15:22:42 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	check_len(const char *number)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (number[i] == '0')
		i++;
	while (number[i] >= '0' && number[i] <= '9')
	{
		len++;
		i++;
	}
	return (len);
}

int	check_long_long_overflow(const char *number)
{
	int		i;
	int		neg;
	int		len;

	i = 0;
	neg = 1;
	len = check_len(number);
	while (number[i] == ' ' || (number[i] > 8 && number[i] < 14))
		i++;
	if (number[i] == '-' || number[i] == '+')
	{
		if (number[i] == '-')
			neg = -1;
		i++;
	}
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (neg == 1 && ft_strncmp(number, "9223372036854775807", 19) > 0)
		return (1);
	if (neg == -1 && ft_strncmp(number, "9223372036854775807", 19) > 1)
		return (1);
	return (0);
}
