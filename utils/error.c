/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:05:19 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/02 12:05:34 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	error_free_prompt(t_ms *ms, char *prompt, char *error)
{
	ms->exit_code = 2;
	ft_putstr_fd("shell-C-smile: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putendl_fd(" error", STDERR_FILENO);
	wclear(0);
	free(prompt);
	return (0);
}
