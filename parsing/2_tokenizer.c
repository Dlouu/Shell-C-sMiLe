/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:03:41 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/02 12:01:10 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	assign_quote_info(t_token *tk)
{
	int	len;

	while (tk)
	{
		len = strlen(tk->content);
		if (tk->content[0] == '\'' && tk->content[len - 1] == '\'')
		{
			tk->squote = 1;
			tk->content = ft_substr(tk->content, 1, len - 2, FALSE);
		}
		else
			tk->squote = 0;
		if (tk->content[0] == '\"' && tk->content[len - 1] == '\"')
		{
			tk->dquote = 1;
			tk->content = ft_substr(tk->content, 1, len - 2, FALSE);
		}
		else
			tk->dquote = 0;
		tk = tk->next;
	}
}

void	assign_token_type(t_ms *ms, t_token *tk, int *command)
{
	if (tk->content[0] == '|')
	{
		tk->type = PIPE;
		*command = 1;
		ms->pipe_count++;
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

int	tokenizer(t_ms *ms)
{
	t_token	*tk;
	int		command;

	tk = ms->token_lexed;
	command = 1;
	assign_quote_info(ms->token_lexed);
	expander(ms, ms->token_lexed, 0);
	recombiner(ms, &ms->token_lexed);
	while (tk)
	{
		assign_token_type(ms, tk, &command);
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
	return (0);
}
