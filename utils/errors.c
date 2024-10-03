/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:05:19 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/03 17:00:36 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(char *error, int exit, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	if (exit == 1)
		clean_exit(exit_code, NULL);
}

void	ft_perror(char *error, int exit)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(error);
	if (exit == 1)
		clean_exit(errno, NULL);
}

void	ft_command_not_found(t_ms *ms, char *cmd, int exit_code)
{
	ms->exit_code = exit_code;
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("command not found", STDERR_FILENO);
	//clean_exit(ms->exit_code, NULL);
}

int	error_parsing(t_ms *ms, char *error)
{
	ms->exit_code = 2;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putendl_fd(" error", STDERR_FILENO);
	wclear(0);
	return (ms->exit_code);
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

void	old_error(char *error, char *details, int critical, int exit_code)
{
	write(2, "minishell: ", 12);
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, details, ft_strlen(details));
	write(2, "\n", 1);
	if (critical == 1)
		clean_exit(exit_code, NULL);
}
