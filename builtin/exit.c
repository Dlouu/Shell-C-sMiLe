/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:12 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 16:56:12 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	too_many_args(t_ms *ms, t_token *tk)
{
	ms->exit_code = 1;
	ms->dont_touch = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tk->content, STDERR_FILENO);
	ft_putendl_fd(": too many arguments", STDERR_FILENO);
	return (1);
}

static int	check_number(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s && s[i])
	{
		while (s[i] && ft_isblank(s[i]))
			i++;
		if (s[i] && ft_issign(s[i]))
			i++;
		while (s[i] && s[i] != '\0')
		{
			if (s[i] && !ft_isdigit(s[i]))
				return (1);
			i++;
		}
		if (s[i] && s[i + 1])
			i++;
	}
	return (0);
}

void	clean_exit(int exit_code, char *error)
{
	if (exit_code == -1)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit_code = 0;
	}
	else if (error)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
	}
	wclear(1);
	exit(exit_code);
}

static void	exit_not_number(t_ms *ms, char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	ms->exit_code = 2;
	clean_exit(ms->exit_code, NULL);
}

int	ft_exit(t_ms *ms, t_token *tk)
{
	long	nbr;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (tk->next && tk->next->next && tk->next->next->type == ARG)
		return (too_many_args(ms, tk->next->next));
	if (tk && tk->next && tk->next->type == ARG)
	{
		if (check_number(tk->next->content) == 0)
		{
			if (!ft_long_ovcheck(tk->next->content))
				return (exit_not_number(ms, tk->next->content), 1);
			nbr = ft_atol(tk->next->content);
			ms->exit_code = nbr % 256;
		}
		else
			exit_not_number(ms, tk->next->content);
	}
	else
		ms->exit_code = 0;
	ft_close_fds_builtins(ms);
	clean_exit(ms->exit_code, NULL);
	return (0);
}
