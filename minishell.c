/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/19 10:22:01 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

//split
//lexer(token)
//parser (virer double pipe, redir vide, etc)
//bonne liste dans l'ordre
//expander (variable et quotes) 
// $t = trim - '$t' ???? - "$t" expand value
//nils

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;
	char	*prompt;

	ms = walloc(sizeof(t_ms), TRUE);
	ms->blank_after_quote = 0;
	get_envp(ms, envp);
	while (1)
	{
		prompt = readline(MAUVE"<Shell-C_sMiLe> "END"$ ");
		if (!prompt)
			break ;
		main_test(ms, argc, argv);
		add_history(prompt);
		if (lexer(ms, prompt) == ERR_QUOTE)
		{
			ms->exit_code = 2;
			printf("Quote error\n");
			free(prompt);
			wclear(0);
			continue ;
		}
		//tokenizer(ms, ms->token_lexed);
		free(prompt);
	}
	(void)argc;
	(void)argv;
	wclear(1);
	return (0);
}
