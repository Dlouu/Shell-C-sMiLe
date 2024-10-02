/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:12 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/02 21:18:29 by mbaumgar         ###   ########.fr       */
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
		while (s && ft_isblank(s[i]))
			i++;
		if (s && ft_issign(s[i]))
			i++;
		while (s && s[i] != '\0')
		{
			if (s && !ft_isdigit(s[i]))
				return (1);
			i++;
		}
		i++;
	}
	return (0);
}

void	clean_exit(int exit_code)
{
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
	clean_exit(ms->exit_code);
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
	// il faut qu'on close un fd dans le cas ou on fait exit > file, j'ai pas su
	// comment faire Nils et Theo aidez moi xD
	clean_exit(ms->exit_code);
	return (0);
}
