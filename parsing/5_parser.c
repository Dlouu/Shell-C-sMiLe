/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:28 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/15 16:34:02 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sort_token(t_ms *ms, t_token **lexed_token)
{
	(void)ms;
	(void)lexed_token;
}

void	pipe_splitter(t_ms *ms)
{
	t_token	*tk;
	t_token	**token_splitted;
	t_token	**head;
	int		i;

	tk = ms->token_lexed;
	i = 0;
	token_splitted = walloc(sizeof(t_token *) * (ms->pipe_count + 2), FALSE);
	head = token_splitted;
	while (tk)
	{
		token_splitted[i] = tk;
		update_index(&tk);
		i++;
	}
	token_splitted[i] = NULL;
	ms->token = head;
}

int	check_types(t_token *token)
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

int	check_redir(t_token *token)
{
	t_token	*tk;

	tk = token;
	while (tk)
	{
		if (tk->type == REDIR_DOUBLE_LEFT && tk->next)
			tk->next->type = DELIMITER;
		if (tk->type == FILENAME && tk->expanded)
			return (0);
		tk = tk->next;
	}
	return (1);
}

static int	count_heredoc(t_ms *ms)
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

int	parser(t_ms *ms, char *prompt)
{
	t_token	*lexed_token;

	lexed_token = ms->token_lexed;
	if (!check_types(lexed_token))
		return (error_free_prompt(ms, prompt, "syntax"));
	if (!check_redir(lexed_token))
		return (error_free_prompt(ms, prompt, "ambiguous redirect"));
	sort_token(ms, &lexed_token);
	pipe_splitter(ms);
	count_heredoc(ms);
	tk_lstprint(ms, ms->token);
	return (1);
}
