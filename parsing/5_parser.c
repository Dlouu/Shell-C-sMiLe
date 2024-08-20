/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:28 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/20 18:08:54 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sort_token(t_ms *ms)
{
	t_token	**tk_lst;
	t_token	*tk;
	t_token	*temp;
	int		i;

	tk_lst = ms->token;
	i = 0;
	temp = NULL;
	while (tk_lst != NULL)
	{
		tk = tk_lst[i];
		while (tk->next)
		{
			if (tk->type == COMMAND || tk->type == BUILTIN)
			{
				printf("add command : %s\n", tk->content);
				tk_lstadd(&temp, tk);
				//tk_delone(ms, ms->token, tk);
			}
			else if (tk->type == ARG)
			{
				printf("add arg : %s\n", tk->content);
				tk_lstadd(&temp, tk);
				//tk_delone(ms, ms->token, tk);
			}
			tk = tk->next;
		}
		temp = tk_lstlast(temp);
		tk = tk_lstfirst(tk);
		temp->next = tk;
		tk->prev = temp;
		temp = tk_lstfirst(temp);
		tk_lst[i] = temp;
		i++;
	}
}

void	split_on_pipe_and_update_index(t_token **tk)
{
	t_token	*temp;
	int		index;

	index = 0;
	while ((*tk)->next && (*tk)->next->type != PIPE)
	{
		(*tk)->index = index;
		index++;
		*tk = (*tk)->next;
	}
	if ((*tk)->next && (*tk)->next->type == PIPE)
	{
		temp = (*tk)->next;
		(*tk)->next = NULL;
		(*tk)->index = index;
		*tk = temp->next;
		(*tk)->prev = NULL;
	}
	else
	{
		(*tk)->index = index;
		*tk = (*tk)->next;
	}
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
		split_on_pipe_and_update_index(&tk);
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

int	parser(t_ms *ms, char *prompt)
{
	t_token	*lexed_token;

	lexed_token = ms->token_lexed;
	if (!check_types(lexed_token))
		return (error_free_prompt(ms, prompt, "syntax"));
	if (!check_redir(lexed_token))
		return (error_free_prompt(ms, prompt, "ambiguous redirect"));
	pipe_splitter(ms);
	//sort_token(ms);
	update_index(ms);
	count_heredoc(ms);
	tk_lstprint(ms, ms->token);
	return (1);
}
