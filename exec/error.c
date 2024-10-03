/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:29:45 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/02 20:45:26 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_perror(char *error, int critical)
{
	write(2, "minishell: ", 12);
	perror(error);
	if (critical == 1)
		clean_exit(errno);
}

void	ft_error(char *error, char *details, int critical, int exit_code)
{
	write(2, "minishell: ", 12);
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, details, ft_strlen(details));
	write(2, "\n", 1);
	if (critical == 1)
		clean_exit(exit_code);
}
