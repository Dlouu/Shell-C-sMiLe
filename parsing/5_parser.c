/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:28 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/19 17:46:19 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	put_arg_after_command(t_token **tk)
{
(void)tk;
}

void	put_command_first(t_token *command_token)
{
	t_token	*tk;
	t_token	*prev_temp;
	t_token	*next_temp;

	tk = command_token;
	prev_temp = command_token->prev;
	next_temp = command_token->next;
	while (tk->index != 0)
		tk = tk->prev;
	command_token->prev = tk->prev;
	command_token->next = tk;
	prev_temp->next = next_temp;
	next_temp->prev = prev_temp;
}

void	sort_token(t_ms *ms)
{
	t_token	*tk;
	//t_token	*head;

	tk = ms->token_lexed;
	while (tk->next)
	{
		if ((tk->type == COMMAND || tk->type == BUILTIN) && tk->index != 0)
		{
			printf("CACA command: %s\n", tk->content);
			put_command_first(tk);
			update_index(&ms->token_lexed);
		}	
		// else if (tk->type == ARG)
		// 	put_arg_after_command(&tk);
		tk = tk->next;
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

int	parser(t_ms *ms, char *prompt)
{
	t_token	*lexed_token;

	lexed_token = ms->token_lexed;
	if (!check_types(lexed_token))
		return (error_free_prompt(ms, prompt, "syntax"));
	if (!check_redir(lexed_token))
		return (error_free_prompt(ms, prompt, "ambiguous redirect"));
	sort_token(ms);
	pipe_splitter(ms);
	count_heredoc(ms);
	tk_lstprint(ms, ms->token);
	return (1);
}
