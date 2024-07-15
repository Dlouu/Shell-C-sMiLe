/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/15 17:33:37 by mbaumgar         ###   ########.fr       */
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
		prompt = readline(MAUVE"<Shell-C_sMiLe>"END"$ ");
		if (!prompt)
			break ;
		// main_test(ms, argc, argv);
		//lexer(ms, argc, argv);
		free(prompt);
	}
	(void)argc;
	(void)argv;
	return (0);
}
