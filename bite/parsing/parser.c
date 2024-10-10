/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:28 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/10 15:53:40 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_command(t_ms *ms)
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
			if (tk->type == COMMAND)
				ms->command_count += 1;
			tk = tk->next;
		}
		i++;
	}
	return (0);
}

void	update_index(t_ms *ms)
{
	int		i;
	int		pipe;
	t_token	*tk;

	pipe = 0;
	while (pipe <= ms->pipe_count)
	{
		i = 0;
		tk = ms->token[pipe];
		while (tk)
		{
			tk->index = i;
			i++;
			tk = tk->next;
		}
		pipe++;
	}
}

static int	check_types(t_token *token)
{
	t_token	*tk;

	tk = token;
	while (tk)
	{
		if (tk->type == PIPE)
		{
			if (!tk->prev || !tk->next || (tk->next && tk->next->type == PIPE))
				return (0);
		}
		else if (tk->type == REDIR_LEFT || tk->type == REDIR_DOUBLE_LEFT || \
		tk->type == REDIR_RIGHT || tk->type == REDIR_DOUBLE_RIGHT)
		{
			if (!tk->next || (tk->next && tk->next->type != FILENAME))
				return (0);
		}
		tk = tk->next;
	}
	return (1);
}

static int	set_delimiter_and_ambiguous_redir(t_token *token)
{
	t_token	*tk;

	tk = token;
	while (tk)
	{
		if (tk->type == REDIR_DOUBLE_LEFT && tk->next)
			tk->next->type = DELIMITER;
		if (tk && tk->type == FILENAME && tk->expanded)
			return (0);
		tk = tk->next;
	}
	return (1);
}

int	parser(t_ms *ms)
{
	t_token	*lexed_token;

	lexed_token = ms->token_lexed;
	if (!check_types(lexed_token))
		return (error_parsing(ms, "syntax"));
	if (!set_delimiter_and_ambiguous_redir(lexed_token))
		return (error_parsing(ms, "ambiguous redirect"));
	pipe_splitter(ms);
	sort_token(ms);
	update_index(ms);
	count_command(ms);
	return (1);
}
