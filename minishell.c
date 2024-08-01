/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/01 20:05:59 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_signal = 0;

//split ok 
//lexer(token) ok
//parser (virer double pipe, redir vide, etc) now
//bonne liste dans l'ordre
//expander (variable et quotes) 
//$t = trim - '$t' ???? - "$t" expand value
//retoken et builtin
//nils
//prompt = readline(MAUVE"<Shell-C_sMiLe> "END"$ ");
//check si a=b c=d echo $a $c mettre le type en arg
//VAR_ENV VAR_EXPORT

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
		if (empty_prompt(prompt) || !lexer(ms, prompt) || tokenizer(ms) \
		|| !parser(ms, prompt))
			continue ;
		find_builtin(ms, ms->token);
		free(prompt);
		wclear(0);
	}
	return (ms->exit_code);
}

void	minishell_init(t_ms *ms, char **argv, char **envp)
{
	ms->exit_code = 0;
	ms->blank_after_quote = 0;
	ms->pipe_count = 0;
	get_envp(ms, envp);
	//rl_catch_signals = 0; //only on linux
	ft_putstr_fd("    ___ _        _ _   ___      __  __ _ _\n", 1);
	ft_putstr_fd("🐚 / __| |_  ___| | | / __|  __|  \\/  (_) |  ___ \n", 1);
	ft_putstr_fd("👀 \\__ \\ ' \\/ -_) | || (__  (_-< |\\/| | | |_/ -_)\n", 1);
	ft_putstr_fd("😃 |___/_||_\\___|_|_| \\___| /__/_|  |_|_|___\\___|\n", 1);
	ft_putstr_fd("                          by niabraha & mbaumgar\n", 1);
	(void)argv;
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
