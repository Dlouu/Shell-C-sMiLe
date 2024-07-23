/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/23 02:29:20 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

//split ok 
//lexer(token) ok
//parser (virer double pipe, redir vide, etc) now
//bonne liste dans l'ordre
//expander (variable et quotes) 
//$t = trim - '$t' ???? - "$t" expand value
//retoken et builtin
//nils
//prompt = readline(MAUVE"<Shell-C_sMiLe> "END"$ ");

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
		add_history(prompt);
		if (lexer(ms, prompt) == ERR_QUOTE)
		{
			ms->exit_code = 2;
			printf("Parsing error : unclosed quote.\n");
			free(prompt);
			wclear(0);
			continue ;
		}
		tokenizer(ms, ms->token_lexed);
		main_test(ms, argc, argv);
		free(prompt);
	}
	wclear(1);
	return (0);
}
