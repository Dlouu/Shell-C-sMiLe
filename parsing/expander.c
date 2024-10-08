/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:06:12 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/08 13:09:59 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	remove_empty_nodes(t_token *head, t_token *tk, t_token *temp)
{
	while (tk)
	{
		if (!tk->content[0] && !tk->next && !tk->prev)
		{
			tk->blank_before = 2;
			tk->blank_after = 2;
			tk->type = COMMAND;
			return ;
		}
		if (!tk->content[0])
		{
			temp = tk;
			tk = tk->next;
			if ((temp->next && temp->next->content[0] == '|' \
			&& (!temp->prev || (temp->prev && temp->prev->content[0] == '|'))) \
			|| (temp->prev && temp->prev->content[0] == '|' \
			&& (!temp->next || (temp->next && temp->next->content[0] == '|'))))
				;
			else
				tk_delone(&head, temp);
		}
		else
			tk = tk->next;
	}
}

static void	skip_invalid_identifier(t_token *tk, int *i)
{
	while (tk->content[*i])
	{
		if (tk->content[*i] && tk->content[*i] == '$')
			break ;
		*i += 1;
	}
}

// Our minishell doesn't support expansion of the following:
	// Character  sequences of the form $'string' are treated as a special
	// variant of single quotes.  The sequence  expands  to  string,  with
	// backslash-escaped characters in string replaced as specified by the
	// NSI C standard.  Backslash escape sequences, if present,  are  de‐
	// coded as follows:
	// 	\a		alert (bell)
	// 	\b		backspace
	// 	[...]	etc, 
	// See the C standard for the complete list of escape sequences.
void	expander(t_ms *ms, t_token *tk, int i)
{
	if (!tk)
		return ;
	while (tk)
	{
		i = 0;
		while (tk && tk->content && *tk->content && tk->content[i])
		{
			if (tk->content[i] && tk->content[i] == '$' && tk->squote == 0)
			{
				if (tk->content[i + 1] && tk->content[i + 1] == '?')
					expand_exit_code(ms, tk, &i);
				else if (tk->content[i + 1] && tk->content[i + 1] == '$')
					expand_pid_number(tk, &i);
				else if (tk->next && (tk->next->squote || tk->next->dquote) \
				&& tk->content[0] == '$' && !tk->content[i + 1])
				{
					tk_delone(&ms->token_lexed, tk);
					i++;
				}
				else if (tk->content[i] && ((tk->content[i + 1] && \
				tk->content[i + 2]) && ((tk->content[i + 1] == '\'' && \
				tk->content[i + 2] == '\'') || (tk->content[i + 1] == '"' \
				&& tk->content[i + 2] == '"'))))
				{
					if (expand_empty_quote(tk, &i))
						continue ;
					else
						break ;
				}
				else if (!tk->content[i + 1])
					break ;
				else if (tk->content[i + 1] && !ft_isalpha(tk->content[i + 1]) \
				&& tk->content[i + 1] != '$' && (tk->content[i + 1] != '?' \
				&& tk->content[i + 1] != '_'))
					skip_invalid_identifier(tk, &i);
				else
					expand_var(ms, tk, &i);
				tk->expanded = 2;
			}
			if (*tk->content && tk->content[i])
				i++;
		}
		tk = tk->next;
	}
	remove_empty_nodes(ms->token_lexed, ms->token_lexed, NULL);
}
