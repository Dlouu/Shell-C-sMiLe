/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/17 16:26:15 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;
	char	*prompt;

	ms = walloc(sizeof(t_ms), TRUE);
	get_envp(ms, envp);
	while (1)
	{
		prompt = readline(MAUVE"<Shell-C_sMiLe> "END"$ ");
		if (!prompt)
			break ;
		//main_test(ms, argc, argv);
		add_history(prompt);
		if (lexer(prompt) == ERR_QUOTE)
		{
			ms->exit_code = 2;
			printf("Quote error\n");
			free(prompt);
			wclear(0);
			continue ;
		}
		free(prompt);
	}
	(void)argc;
	(void)argv;
	wclear(1);
	return (0);
}
