/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/04 16:28:23 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_signal = 0;

/*
TRUCS A CHECK
[_]	path si on en trouve pas au lancement, faut qu'on en assign un genre de 
	base genre /bin/bash ?
[_] si on unset PATH il faut que ca ne marche pas mais no segfault
- - - - - - -
PARSING
[_] $""aa$"" a fixer
[_] expand dollar a refaire
[_] signaux
[_] heredoc no expansion
- - - - - - -
EXECUTION
[_]	heredoc
- - - - - - -
COMMON
[_] exit-code
[_] free
*/

void	increase_shlvl(t_ms *ms)
{
	int	shlvl;

	shlvl = 0;
	if (!find_env_node(ms->env, "SHLVL"))
		add_env_node(ms, "SHLVL=0");
	shlvl = ft_atoi(find_env_value(ms->env, "SHLVL"));
	if (shlvl > 0 && shlvl < 1000)
		replace_env_value(ms->env, "SHLVL", (ft_itoa(shlvl + 1, TRUE)));
	else
		replace_env_value(ms->env, "SHLVL", "1");
}

void	minishell_init(t_ms *ms, char **argv, char **envp)
{
	ms->exit_code = 0;
	ms->blank_before = 0;
	ms->blank_after = 0;
	ms->dollar = 0;
	ms->pipe_count = 0;
	ms->heredoc_count = 0;
	ms->i = 0;
	ms->command_count = 0;
	ms->prompt = NULL;
	ms->old_path = NULL;
	ms->new_path = NULL;
	get_envp(ms, envp);
	increase_shlvl(ms);
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
		ms->pipe_count = 0;
		ms->heredoc_count = 0;
		ms->command_count = 0;
		ms->i = 0;
		printf("signal = READLINE / pid %d \n", getpid());
		set_signals(READLINE);
		prompt = readline(MAUVE"<Shell-C_sMiLe> "END"$ ");
		if (!prompt)
			clean_exit(-1, NULL);
		ms->prompt = ft_strdup(prompt, 0);
		free(prompt);
		add_history(ms->prompt);
		if (empty_prompt(ms->prompt) || !lexer(ms, ms->prompt, NULL) || \
		tokenizer(ms) || !parser(ms))
			continue ;
		//tk_lstprint(ms, ms->token);
		ms->exit_code = exec_main(ms);
		wclear(0);
	}
	return (ms->exit_code);
}

//voir le exit(0) du exec a changer pour le recuperer ici et free

int	main(int argc, char **argv, char **envp)
{
	t_ms		*ms;
	int			exit_code;

	exit_code = 0;
	if (argc != 1)
		return (printf("error : minishell doesn't take arguments\n"), 1);
	ms = walloc(sizeof(t_ms), TRUE);
	minishell_init(ms, argv, envp);
	minishell_loop(ms);
	rl_clear_history();
	exit_code = ms->exit_code;
	wclear(1);
	return (exit_code);
}

//faut check si quand ya pas de cmd et juste des redir
//ca fout pas la merde dans l'execution
//check pour add le prompt a la struc et la free direct
//ou bien le mettre dans le garbage
