/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_ovcheck.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:25:29 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/12 16:54:44 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"


int    ft_long_ovcheck(const char *number)
{
	if (ft_atoi(number) != atoll(number)) //bite
		return (0);
	return 1;
}


