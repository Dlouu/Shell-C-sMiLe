/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 00:12:48 by dlou              #+#    #+#             */
/*   Updated: 2024/10/03 13:50:20 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sigint_handler_in_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		g_signal = SIGINT;
	}
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("^C", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 130; // SIGINT ?
	}
}

void	set_signals(int signum, int type, int flags, void (*handler)(int))
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		clean_exit(EXIT_FAILURE, "sigemptyset error");
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
		clean_exit(EXIT_FAILURE, "sigaction error");
}

void	reset_default_signals(void)
{
	set_signals(SIGINT, SIG_DEFAULT, SIG_REST_SIGINFO, NULL);
	set_signals(SIGQUIT, SIG_DEFAULT, SIG_REST_SIGINFO, NULL);
}

void	set_custom_signals(void)
{
	set_signals(SIGINT, SIG_INTERACTIVE, SIG_REST_SIGINFO, &sigint_handler);
	set_signals(SIGQUIT, SIG_IGNORE, SIG_REST_SIGINFO, NULL);
}

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
