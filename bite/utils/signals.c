/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:24:34 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/10 17:24:42 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	readline_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = SIGINT;
	}
}

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "^C\n", 3);
	}
	if (signum == SIGQUIT)
		g_signal = SIGQUIT;
}

void	heredoc_sigaction_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = heredoc_signal_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	fork_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "^C\n", 3);
		g_signal = SIGINT;
	}
	if (signum == SIGQUIT)
		g_signal = SIGQUIT;
}

void	set_signals(t_signal_type mode)
{
	if (mode == READLINE)
	{
		signal(SIGINT, readline_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == FORK)
	{
		signal(SIGINT, fork_signal_handler);
		signal(SIGQUIT, fork_signal_handler);
	}
	else if (mode == SILENCE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		heredoc_sigaction_handler();
		signal(SIGQUIT, SIG_IGN);
	}
}
