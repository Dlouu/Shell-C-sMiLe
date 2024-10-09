/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:29:45 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 14:41:30 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error_no_exit(char *error, char *details, t_ms *ms, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(details, STDERR_FILENO);
	ms->dont_touch = 1;
	ms->exit_code = exit_code;
}

void	ft_perror(char *error, int critical)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(error);
	if (critical == 1)
		clean_exit(errno, NULL);
}

void	ft_error(char *error, char *details, int critical, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(details, STDERR_FILENO);
	if (critical == 1)
		clean_exit(exit_code, NULL);
}

int	error_parsing(t_ms *ms, char *error)
{
	ms->exit_code = 2;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putendl_fd(" error", STDERR_FILENO);
	wclear(0);
	return (0);
}

int	empty_prompt(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (!ft_isblank(prompt[i]))
			return (0);
	}
	return (1);
}
