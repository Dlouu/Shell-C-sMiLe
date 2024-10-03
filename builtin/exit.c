/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:12 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/03 18:13:49 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (error)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
	}
	wclear(1);
	exit(exit_code);
}

static void	exit_too_many_args(t_ms *ms)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	ms->exit_code = 1;
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
		return (exit_too_many_args(ms), 1);
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
	//ft_close_fds_builtins(ms->px); // ca segfault, a check
	clean_exit(ms->exit_code, NULL);
	return (0);
}
