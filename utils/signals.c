/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 00:12:48 by dlou              #+#    #+#             */
/*   Updated: 2024/08/01 02:00:22 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
	}
}

void	set_signals(int signum, int type, int flags, void (*handler)(int))
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
	{
		wclear(1);
		exit(EXIT_FAILURE);
	}
	if (flags == SIG_REST_SIGINFO)
		sa.sa_flags = SA_RESTART | SA_SIGINFO;
	else
		sa.sa_flags = flags;
	sa.sa_handler = handler;
	if (type == SIG_INTERACTIVE)
		sa.sa_handler = sigint_handler;
	if (type == SIG_IGNORE)
		sa.sa_handler = SIG_IGN;
	if (type == SIG_DEFAULT)
		sa.sa_handler = SIG_DFL;
	if (sigaction(signum, &sa, NULL) == -1)
	{
		wclear(1);
		exit(EXIT_FAILURE);
	}
}

void	set_interactive_signals(void)
{
	set_signals(SIGINT, SIG_INTERACTIVE, SIG_REST_SIGINFO, &sigint_handler);
	set_signals(SIGQUIT, SIG_IGNORE, SIG_REST_SIGINFO, NULL);
}
