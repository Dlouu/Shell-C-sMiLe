/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:12 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/02 17:59:43 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_number(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (1);
	while (s[++i])
	{
		while (ft_isblank(s[i]))
			i++;
		if (ft_issign(s[i]))
			i++;
		while (s[i] != '\0')
		{
			if (!ft_isdigit(s[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

void	clean_exit(int exit_code)
{
	wclear(1);
	exit(exit_code);
}

static void	exit_not_number(t_ms *ms, char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required\n", STDERR_FILENO);
	ms->exit_code = 2;
	printf("exit code : %d\n", ms->exit_code);
	exit(ms->exit_code);
}

int	ft_exit(t_ms *ms, t_token *tk)
{
	long	nbr;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (tk->next)
	{
		if (check_number(tk->next->content) == 0)
		{
			if (tk->next->next)
			{
				ft_putendl_fd("minishell: exit: too many arguments", 2);
				ms->exit_code = 1;
				exit(ms->exit_code);
				return (1);
			}
			else
			{
				if (!ft_long_ovcheck(tk->next->content))
				{
					exit_not_number(ms, tk->next->content);
					return (1);
				}
				nbr = ft_atol(tk->next->content);
				ms->exit_code = nbr % 256;
			}
			printf("exit code : %d\n", ms->exit_code);
		}
		else
			exit_not_number(ms, tk->next->content);
	}
	else
		ms->exit_code = 0;
	clean_exit(ms->exit_code);
	return (0);
}
