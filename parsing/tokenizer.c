/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:03:41 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/23 04:49:46 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/typedefs.h"

void	split_pipe(t_ms *ms, t_token *lexed_token)
{
	t_token	*tk;
	t_token	*temp;
	t_token	**token_splitted;
	t_token	**head;
	int		i;
	int		index;

	index = 0;
	tk = lexed_token;
	i = 0;
	token_splitted = NULL;
	token_splitted = walloc(sizeof(t_token *) * (ms->pipe_count + 1), FALSE);
	head = token_splitted;
	while (tk)
	{
		token_splitted[i] = tk;
		index = 0;
		while (tk->next && tk->next->type != PIPE)
		{
			tk->index = index;
			index++;
			tk = tk->next;
		}
		if (tk->next && tk->next->type == PIPE)
		{
			temp = tk->next;
			tk->next = NULL;
			tk->index = index;
			tk = temp->next;
		}
		else
		{
			tk->index = index;
			tk = tk->next;
		}
		i++;
	}
	ms->token = head;
}

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
		{
			tk->squote = 0;
		}
		if (tk->content[0] == '\"' && tk->content[len - 1] == '\"')
		{
			tk->dquote = 1;
			tk->content = ft_substr(tk->content, 1, len - 2, FALSE);
		}
		else
		{
			tk->dquote = 0;
		}
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

void	tokenizer(t_ms *ms, t_token *lexed_token)
{
	t_token	*tk;
	int		command;

	tk = lexed_token;
	command = 1;
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
	assign_quote_info(lexed_token);
	split_pipe(ms, lexed_token);
	tk_lstprint(ms, ms->token);
	(void)ms;
}
