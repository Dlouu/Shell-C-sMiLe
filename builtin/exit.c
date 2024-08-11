/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:12 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/11 22:36:21 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int check_number(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] == '-' || s[i] == '+')
			i++;
		while (s[i] != '\0')
		{
			if (s[i] < '0' || s[i] > '9')
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

static int exit_not_number(char *str)
{
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": numeric argument required\n", 29);
	return (255);
}

int	ft_exit(t_ms *ms)
{
	write(STDERR_FILENO, "exit\n", 5);
	if (ms->token_lexed->next)
	{
		if (check_number(ms->token_lexed->next->content) == 0) // c'est un nombre
		{
			if (ms->token_lexed->next->next)
				return (write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36), 1); //Shell-C-sMiLe
			else
				ms->exit_code = ft_atoi(ms->token_lexed->next->content);
		}
		else
			ms->exit_code = exit_not_number(ms->token_lexed->next->content); // pas un nombre. doit quitter.
	}
	else
		ms->exit_code = 0;
	clean_exit(ms);
	return (ms->exit_code);
}
