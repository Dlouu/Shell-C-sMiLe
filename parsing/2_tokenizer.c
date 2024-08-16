/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_tokenizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:03:41 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/17 01:47:14 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_heredoc(t_ms *ms)
{
	t_token	**tk_lst;
	t_token	*tk;
	int		i;

	tk_lst = ms->token;
	i = 0;
	while (tk_lst[i])
	{
		tk = tk_lst[i];
		while (tk->next)
		{
			if (tk->type == REDIR_DOUBLE_LEFT)
				ms->heredoc_count += 1;
			tk = tk->next;
		}
		i++;
	}
	return (0);
}

void	assign_command_type(t_token *tk, int *command, int i)
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
					tk->builtin = 1;
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

void	assign_token_type(t_ms *ms, t_token *tk)
{
	if (tk->type == -1 && tk->content[0] == '|')
	{
		tk->type = PIPE;
		ms->pipe_count++;
	}
	else if (tk->type == -1 && tk->content[0] == '>')
	{
		if (tk->content[1] && tk->content[1] == '>')
			tk->type = REDIR_DOUBLE_RIGHT;
		else
			tk->type = REDIR_RIGHT;
	}
	else if (tk->type == -1 && tk->content[0] == '<')
	{
		if (tk->content[1] && tk->content[1] == '<')
			tk->type = REDIR_DOUBLE_LEFT;
		else
			tk->type = REDIR_LEFT;
	}
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
	assign_quote_info(ms->token_lexed);
	expander(ms, ms->token_lexed, 0);
	recombiner(ms->token_lexed);
	word_splitter(&ms->token_lexed);
	while (tk)
	{
		assign_token_type(ms, tk);
		tk = tk->next;
	}
	assign_command_type(ms->token_lexed, &command, 0);
	return (0);
}
