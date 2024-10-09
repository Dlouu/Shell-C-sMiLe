/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 00:12:48 by dlou              #+#    #+#             */
/*   Updated: 2024/10/09 14:56:16 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* READLINE */
// ETAT		OK
// Ctrl C	dans le prompt = ^C\n  (quitte le prompt, = newline)
// Ctrl D	dans le prompt = exit\n  (quitte le programme)
// CTrl \	(ne fait rien)
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

/* HEREDOC */
// ETAT	 	J'ai des signaux a mute je comprend pas ALED
// Ctrl C	dans le prompt = ^C\n  (quitte le heredoc)
// Ctrl D	quitte  + message d'erreur
//bash: warning: here-document at line 2 delimited by end-of-file (wanted `lol')
// CTrl \	(ne fait rien)
void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	heredoc_sigaction_handler(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = heredoc_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	// sa.sa_handler = SIG_IGN;
	// sigaction(SIGQUIT, &sa, NULL);
}

/* FORK */
// ETAT		OK
// Ctrl C	dans un block = ^C\n
// Ctrl \	(cat|cat|ls  ^\ sans newline
//			grep '' = ^\Quit\n avec newline
// Ctrl D	quite le prompt avec juste une newline
void	fork_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
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
