/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 00:12:48 by dlou              #+#    #+#             */
/*   Updated: 2024/10/05 13:58:10 by mbaumgar         ###   ########.fr       */
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
		write(STDOUT_FILENO, "^R\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
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
		//write(STDOUT_FILENO, "^H\n", 3);
		//rl_replace_line("", 0);
		// rl_on_new_line();
		rl_redisplay();
		close(STDIN_FILENO);
		g_signal = 130;
	}
	// if (signum == SIGQUIT)
	// {
	// 	//(void)signum;
	// 	//write(STDOUT_FILENO, "\r>   ", 6);
	// 	//rl_replace_line("\r>     test", 12);
	// 	//close(STDIN_FILENO);
	// 	//g_signal = 131;
	// }
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
		write(STDOUT_FILENO, "^F\n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130;
	}
	if (signum == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit\n", 5);
		g_signal = 131;
	}
}

void	set_signals(t_signal_type mode)
{
	if (mode == READLINE)
	{
		signal(SIGINT, readline_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC)
	{
		signal(SIGINT, heredoc_signal_handler);
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
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
