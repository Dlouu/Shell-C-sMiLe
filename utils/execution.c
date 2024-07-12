/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:50:11 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/12 16:12:02 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_message(const char *message, int exit_status)
{
	ft_printf(message);
	exit(exit_status);
}

void	free_lst(t_test **a_stack)
{
	t_test	*tmp;

	while (a_stack && *a_stack)
	{
		tmp = *a_stack;
		*a_stack = (*a_stack)->next;
		free(tmp);
	}
	a_stack = NULL;
}
