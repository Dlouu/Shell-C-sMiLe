/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/09 15:46:15 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	g_signal = 0;

/*
TRUCS A CHECK
[_]	path si on en trouve pas au lancement, faut qu'on en assign un genre de 
	base genre /bin/bash ?
[_] si on unset PATH il faut que ca ne marche pas mais no segfault
[_] signaux
[_] heredoc no expansion
[_]	heredoc kill
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

void	configure_terminal(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

void	minishell_init(t_ms *ms, char **argv, char **envp)
{
	(void)argv;
	configure_terminal();
	ms->exit_code = 0;
	ms->blank_before = 0;
	ms->blank_after = 0;
	ms->dollar = 0;
	ms->pipe_count = 0;
	ms->i = 0;
	ms->command_count = 0;
	ms->prompt = NULL;
	ms->old_path = NULL;
	ms->new_path = NULL;
	ms->dont_touch = 0;
	get_envp(ms, envp);
	increase_shlvl(ms);
	rl_catch_signals = 0;
	ft_putstr_fd("42 project | minishell | as beautiful as a shell~\n", 1);
	ft_putstr_fd("    ___ _        _ _   ___      __  __ _ _\n", 1);
	ft_putstr_fd("🐚 / __| |_  ___| | | / __|  __|  \\/  (_) |  ___\n", 1);
	ft_putstr_fd("👀 \\__ \\ ' \\/ -_) | || (__  (_-< |\\/| | | |_/ -_)\n", 1);
	ft_putstr_fd("😃 |___/_||_\\___|_|_| \\___| /__/_|  |_|_|___\\___|\n", 1);
	ft_putstr_fd("                           by niabraha & mbaumgar\n", 1);
}

int	minishell_loop(t_ms *ms)
{
	char	*prompt;

	while (1)
	{
		ms->pipe_count = 0;
		ms->command_count = 0;
		ms->i = 0;
		set_signals(READLINE);
		prompt = readline(MAUVE"<Shell-C_sMiLe> "END"$ ");
		if (!prompt)
			clean_exit(-1, NULL);
		ms->prompt = ft_strdup(prompt, 0);
		if (prompt)
			add_history(prompt);
		free(prompt);
		if (empty_prompt(ms->prompt) || !lexer(ms, ms->prompt, NULL) || \
		tokenizer(ms) || !parser(ms))
			continue ;
		ms->exit_code = exec_main(ms);
		printf("exit code : %d\n", ms->exit_code);
		wclear(0);
	}
	return (ms->exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms		*ms;
	int			exit_code;

	exit_code = 0;
	if (argc != 1)
		return (printf("error : minishell doesn't take arguments\n"), 1);
	ms = walloc(sizeof(t_ms), TRUE);
	minishell_init(ms, argv, envp);
	exit_code = minishell_loop(ms);
	rl_clear_history();
	wclear(1);
	return (exit_code);
}
