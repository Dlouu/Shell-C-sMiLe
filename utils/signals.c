/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 00:12:48 by dlou              #+#    #+#             */
/*   Updated: 2024/09/12 17:32:02 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// si t'arrives pas a compiler sur ton mac,
// mets rl_replace_line("", 0); en commentaire ligne 22
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