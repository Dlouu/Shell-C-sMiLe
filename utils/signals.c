/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 00:12:48 by dlou              #+#    #+#             */
/*   Updated: 2024/10/04 16:41:24 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "^H\n", 3);
		rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		// close(STDIN_FILENO);
		g_signal = 130;
	}
	// if (signum == SIGQUIT)
	// {
	// 	write(STDOUT_FILENO, "Quit\n", 5);
	// 	close(STDIN_FILENO);
	// 	g_signal = 131;
	// }
}

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
/*
a modifier :
cat|cat|ls Ctrl C newline
cat Ctrl C newline
cat Ctrl \Quit
heredoc Ctrl D erreur
		Ctrl \ ignore
*/

/*
BASH

PROMPT READLINE
Ctrl + C dans le prompt = ^C\n  (quitte le prompt, = newline)
Ctrl + D dans le prompt = exit\n  (quitte le programme)
CTrl + \ dans le prompt = (ne fait rien)

HEREDOC
	Ctrl C			| 	Ctrl D								| 	Ctrl \
$ echo bite << lol	| echo bite << lol						| echo bite << lol
> ^C				| > 									| ne fait rien
$ 					| bash: warning: here-document at line 2 
.					| delimited by end-of-file (wanted `lol')
.					| bite									|
.					| $ 									|
Ctrl C new prompt	| CTRL+D il fait la commande + erreur	| Ctrl \ = A ignorer

BLOCK/PIPE/FORK/TRUC ?
Ctrl C 	dans un block = ^C\n  (quitte le block, = newline)
Ctrl \	(cat : Ctrl \ dans un block = ^\ sans newline faut surement osef)
		grep '' = ^\Quit\n avec newline
Ctrl D 	quite le prompt avec juste une newline
*/
