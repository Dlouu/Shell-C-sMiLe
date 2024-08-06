/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/06 10:19:53 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_signal = 0;

/*
TRUCS A CHECK
[_]	path si on en trouve pas au lancement, faut qu'on en assign un genre de base
	genre /bin/bash ?
[_]	si on unset USER est-ce que ca marche ?
[_] si on unset PATH il faut que ca ne marche pas mais no segfault
- - - - - - -
PARSING
[x]	lexer (creation de la liste)
[x]	tokenizer (assigner les types)
[x]	expander (expand les variables)
[_]	recombiner (recoller les nodes "" et '' accolées)
[_]	word_splitter (split les tokens "" expand)
[_] token_sorter (sort les tokens dans l'ordre d'execution)
[x] parsing
- - - - - - -
EXECUTION
[~]	builtin reste exit, cd et unset
[_]	fork
[_]	pipe
[_]	redirections > >> < <<
[_]	waitpid cat | cat | ls
*/

int	empty_prompt(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (!ft_isblank(prompt[i]))
			return (0);
	}
	free(prompt);
	return (1);
}

// si t'arrives pas a compiler sur ton mac,
// mets rl_catch_signals = 0; en commentaire ligne 65
// et egalement dans le fichier utils/signal.c ligne 22
void	minishell_init(t_ms *ms, char **argv, char **envp)
{
	ms->exit_code = 0;
	ms->blank_before_quote = 0;
	ms->blank_after_quote = 0;
	ms->pipe_count = 0;
	get_envp(ms, envp);
	//rl_catch_signals = 0;
	ft_putstr_fd("42 project | minishell | as beautiful as a shell~\n", 1);
	ft_putstr_fd("    ___ _        _ _   ___      __  __ _ _\n", 1);
	ft_putstr_fd("🐚 / __| |_  ___| | | / __|  __|  \\/  (_) |  ___\n", 1);
	ft_putstr_fd("👀 \\__ \\ ' \\/ -_) | || (__  (_-< |\\/| | | |_/ -_)\n", 1);
	ft_putstr_fd("😃 |___/_||_\\___|_|_| \\___| /__/_|  |_|_|___\\___|\n", 1);
	ft_putstr_fd("                           by niabraha & mbaumgar\n", 1);
	(void)argv;
}

int	minishell_loop(t_ms *ms)
{
	char	*prompt;

	while (1)
	{
		set_interactive_signals();
		prompt = readline(MAUVE"<Shell-C_sMiLe> "END"$ ");
		if (!prompt)
			break ;
		add_history(prompt);
		if (empty_prompt(prompt) || !lexer(ms, prompt, NULL) || tokenizer(ms) \
		|| !parser(ms, prompt))
			continue ;
		find_builtin(ms, ms->token);
		free(prompt);
		wclear(0);
	}
	return (ms->exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	if (argc != 1)
		return (printf("error : shell-C-smile doesn't take arguments\n"), 1);
	ms = walloc(sizeof(t_ms), TRUE);
	minishell_init(ms, argv, envp);
	minishell_loop(ms);
	wclear(1);
	return (0);
}
