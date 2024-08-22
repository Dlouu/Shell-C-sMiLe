/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:23:55 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/22 13:41:57 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	go_to_next_quote(char *prompt, int *i, int *quote, int quote_type)
{
	(*i)++;
	(*quote)++;
	while (prompt[*i] && !(ft_isquote(prompt[*i]) == quote_type))
		(*i)++;
	if (ft_isquote(prompt[*i]) == quote_type)
		(*quote)--;
}
