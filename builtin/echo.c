/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:06 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/03 16:33:01 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(t_ms **lst)
{
	if ((*lst)->next == NULL)
		return (write(1, "\n", 1), 0);
	(*lst) = (*lst)->next;
	if (ft_strncmp((*lst)->content, "-n\0", 3) == 0)
	{
		while ((*lst)->next != NULL)
		{
			(*lst) = (*lst)->next;
			write(1, (*lst)->content, ft_strlen((*lst)->content));
			if ((*lst)->next != NULL)
				write(1, " ", 1);
		}
		write(1, "", 0);
	}
	else
		ft_printf("gros caca\n");
	return (0);
}

/* notes :
Faire attention echo -nnnnn -nnnlol -n lol
utiliser des write plutot que des printf (conseil de Max)
echo -nnnn5 -n lol
echo -nn5 -n -nnn5 lol
*/
