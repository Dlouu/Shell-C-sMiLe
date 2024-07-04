/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:06 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/04 19:21:41 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
valide + valide  echo -n -n bite (bite sans saut de ligne)
valide + pas valide echo -n -n5 bite (-n5 bite sans saut de ligne)
pas valide + valide saut de ligne
pas valide + pas valide

tant que y'a -n ou -nnnn je skip, j'ecris des que ca change. sans \name
sinon jecris tout
*/


#include "../inc/minishell.h"

int	ft_echo(t_ms **lst)
{
	int		n_flag;
	t_ms	*tmp;

	n_flag = 0;
	tmp = (*lst)->next; // skip echo a enlever plus tard
	while (tmp != NULL)
	{
		if (tmp->content[0] == '-')
		{
			int i = 1;
			while (tmp->content[i] == 'n')
				i++;
			if (tmp->content[i] == '\0')
				n_flag = 1;
		}
		else
		{
			write(1, tmp->content, ft_strlen(tmp->content));
			if (tmp->next != NULL)
				write(1, " ", 1);
		}
		tmp = tmp->next;
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	return (0);
}

/* notes :
Faire attention echo -nnnnn -nnnlol -n lol
utiliser des write plutot que des printf (conseil de Max)
echo -nnnn5 -n lol
echo -nn5 -n -nnn5 lol
*/
