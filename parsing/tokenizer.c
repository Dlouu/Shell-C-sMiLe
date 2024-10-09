/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:03:41 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/09 17:16:26 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	set_quote_info(t_token *tk)
{
	int	len;

	while (tk)
	{
		len = ft_strlen(tk->content);
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

static void	set_command_type(t_token *tk, int *command, int i)
{
	static char	*builtin_cmd[] = \
			{"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};

	while (tk)
	{
		if (tk->type == ARG && *command == 1)
		{
			i = -1;
			while (builtin_cmd[++i])
			{
				if (tk->content && ft_strcmp(tk->content, builtin_cmd[i]) == 0)
				{
					tk->type = BUILTIN;
					break ;
				}
			}
			if (tk->type != BUILTIN)
				tk->type = COMMAND;
			*command = 0;
		}
		else if (tk->type == PIPE)
			*command = 1;
		tk = tk->next;
	}
}

static void	set_redir_type(t_token *tk, int redir_1, int redir_2, char c)
{
	if (tk->content[1] && tk->content[1] == c && !tk->squote && !tk->dquote)
		tk->type = redir_2;
	else
		tk->type = redir_1;
}

void	set_token_type(t_ms *ms, t_token *tk)
{
	if (tk->type == -1 && tk->content[0] == '|' \
	&& !tk->dquote && !tk->squote && !tk->expanded)
	{
		tk->type = PIPE;
		ms->pipe_count++;
	}
	else if (tk->type == -1 && tk->content[0] == '>' \
	&& !tk->squote && !tk->dquote && !tk->expanded)
		set_redir_type(tk, REDIR_RIGHT, REDIR_DOUBLE_RIGHT, '>');
	else if (tk->type == -1 && tk->content[0] == '<' \
	&& !tk->squote && !tk->dquote && !tk->expanded)
		set_redir_type(tk, REDIR_LEFT, REDIR_DOUBLE_LEFT, '<');
	else if (tk->type == -1 && (tk->prev && (tk->prev->type >= 3 && \
	tk->prev->type <= 6)))
		tk->type = FILENAME;
	else if (tk->type == -1)
		tk->type = ARG;
}

int	tokenizer(t_ms *ms)
{
	t_token	*tk;
	int		command;

	tk = ms->token_lexed;
	command = 1;
	set_quote_info(ms->token_lexed);
	expander(ms, ms->token_lexed);
	word_splitter(ms, 0);
	while (tk)
	{
		set_token_type(ms, tk);
		tk = tk->next;
	}
	recombiner(ms->token_lexed);
	set_command_type(ms->token_lexed, &command, 0);
	return (0);
}
