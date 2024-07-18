/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:03:41 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/18 14:39:06 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/typedefs.h"

void	tokenizer(t_ms *ms, t_token *lexed_token)
{
	t_token	*tk;

	tk = lexed_token;
	while (tk)
	{
		if (tk->content[0] == '|')
			tk->type = PIPE;
		else if (tk->content[0] == '>')
		{
			if (tk->content[1] == '>')
				tk->type = REDIR_DOUBLE_RIGHT;
			else
				tk->type = REDIR_RIGHT;
		}
		else if (tk->content[0] == '<')
		{
			if (tk->content[1] == '<')
				tk->type = REDIR_DOUBLE_LEFT;
			else
				tk->type = REDIR_LEFT;
		}
		else if ((tk->type == -1 && ((tk->index == 0) || (tk->prev && \
		tk->prev->type == PIPE) || ((tk->prev && tk->prev->type == FILENAME) \
		&& (tk->index == 2 || (tk->prev->prev->prev && \
		tk->prev->prev->prev->type == PIPE))))))
			tk->type = COMMAND;
		else if (tk->prev && (tk->prev->type >= 3 && tk->prev->type <= 6))
		{
			if (tk->type == -1)
				tk->type = FILENAME;
		}
		else
		{
			if (tk->type == -1)
				tk->type = ARG;
		}
		tk = tk->next;
		(void)ms;
	}
	tk_lstprint(lexed_token);
}