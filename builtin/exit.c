/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:12 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/12 17:30:03 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int check_number(char *s)
{
	int i;

	i = -1;
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

static void clean_exit(t_ms *ms)
{
	//close les fd
	//free les mallocs
	//free les listes
	(void)ms;
	sigaction(SIGQUIT, NULL, NULL);
}

static void exit_not_number(t_ms *ms, char *str)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": numeric argument required\n", 29);
	ms->exit_code = 2;
	printf("exit code : %d\n", ms->exit_code);
	exit(ms->exit_code);
}

int	ft_exit(t_ms *ms)
{
	long nbr;
	write(STDERR_FILENO, "exit\n", 5);
	if (ms->token_lexed->next)
	{
		if (check_number(ms->token_lexed->next->content) == 0)
		{
			if (ms->token_lexed->next->next)
			{
				write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
				ms->exit_code = 1;
				exit(ms->exit_code);
				return (1);
			}
			else
			{
				if (!ft_long_ovcheck(ms->token_lexed->next->content))
				{
					exit_not_number(ms, ms->token_lexed->next->content);
					return (1);
				}
				nbr = ft_atol(ms->token_lexed->next->content);
				ms->exit_code = nbr % 256;
				if (nbr < 0)
					ms->exit_code += 256;
			}
			printf("exit code : %d\n", ms->exit_code);
		}
		else
			exit_not_number(ms, ms->token_lexed->next->content);
	}
	else
		ms->exit_code = 0;
	clean_exit(ms);
	return (exit(ms->exit_code), 0);
}
