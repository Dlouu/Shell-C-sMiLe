/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:03:41 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/19 13:18:30 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/typedefs.h"

void	assign_token_type(t_token *tk, int *command)
{
	if (tk->content[0] == '|')
	{
		tk->type = PIPE;
		*command = 1;
	}
	else if (tk->content[0] == '>')
	{
		if (tk->content[1] && tk->content[1] == '>')
			tk->type = REDIR_DOUBLE_RIGHT;
		else
			tk->type = REDIR_RIGHT;
	}
	else if (tk->content[0] == '<')
	{
		if (tk->content[1] && tk->content[1] == '<')
			tk->type = REDIR_DOUBLE_LEFT;
		else
			tk->type = REDIR_LEFT;
	}
	else if (tk->type == -1 && (tk->prev && (tk->prev->type >= 3 && \
	tk->prev->type <= 6)))
		tk->type = FILENAME;
}

void	tokenizer(t_ms *ms, t_token *lexed_token)
{
	t_token	*tk;
	int		command;

	tk = lexed_token;
	command = 1;
	while (tk)
	{
		assign_token_type(tk, &command);
		if (command && (tk->type == -1))
		{
			tk->type = COMMAND;
			command = 0;
		}
		else
		{
			if (tk->type == -1)
				tk->type = ARG;
		}
		tk = tk->next;
	}
	tk_lstprint(lexed_token);
	(void)ms;
}
