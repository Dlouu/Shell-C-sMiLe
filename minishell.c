/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/09/19 17:39:43 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_signal = 0;

/*
TRUCS A CHECK
[_]	path si on en trouve pas au lancement, faut qu'on en assign un genre de 
	base genre /bin/bash ?
[_]	si on unset USER est-ce que ca marche ?
[_] si on unset PATH il faut que ca ne marche pas mais no segfault
- - - - - - -
PARSING
[x]	lexer (creation de la liste)
[x]	tokenizer (assigner les types)
[x]	expander (expand les variables)
[x]	recombiner (recoller les nodes "" et '' accolées)
[x]	word_splitter (split les tokens "" expand)
[x] token_sorter (sort les tokens dans l'ordre d'execution)
[x] parsing
[_] check $USER$USER$blah$blah = ne delete pas les 2 blah (la solution etait de
	split sur les $ mais depuis avec $ dans isseparator infinite loop
[_] $""aa$"" a fixer
- - - - - - -
EXECUTION
[~]	builtin reste exit, cd et unset
[x]	fork
[_]	pipe
[_]	redirections > >> < <<
[_]	waitpid cat | cat | ls
*/

// si t'arrives pas a compiler sur ton mac,
// mets rl_catch_signals = 0; en commentaire ligne 55
// et egalement dans le fichier utils/signal.c ligne 22
void	minishell_init(t_ms *ms, char **argv, char **envp)
{
	ms->exit_code = 0;
	ms->blank_before_quote = 0;
	ms->blank_after_quote = 0;
	ms->dollar = 0;
	ms->pipe_count = 0;
	ms->heredoc_count = 0;
	ms->heredoc_count_check = 0;
	ms->command_count = 0;
	ms->current_pipe = 0;
	get_envp(ms, envp);
	rl_catch_signals = 0;
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
		set_custom_signals();
		prompt = readline(MAUVE"<Shell-C_sMiLe> "END"$ ");
		if (!prompt)
			break ;
		add_history(prompt);
		if (empty_prompt(prompt) || !lexer(ms, prompt, NULL) || tokenizer(ms) \
		|| !parser(ms, prompt))
			continue ;
		//tk_lstprint(ms, ms->token);
		exec_main(ms);
		free(prompt);
		ms->pipe_count = 0;
		ms->heredoc_count = 0;
		ms->command_count = 0;
		ms->current_pipe = 0;
		ms->heredoc_count_check = 0;
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

//faut check si quand ya pas de cmd et juste des redir
//ca fout pas la merde dans l'execution
//check pour add le prompt a la struc et la free direct
//ou bien le mettre dans le garbage