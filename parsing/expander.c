/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:06:12 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/08 19:36:14 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	skip_invalid_identifier(t_token *tk, int *i)
{
	while (tk->content[*i])
	{
		if (tk->content[*i] && tk->content[*i] == '$')
			break ;
		*i += 1;
	}
}

static int	is_invalid_identifier(t_token *tk, int *i)
{
	if (tk->content[*i + 1] && !ft_isalpha(tk->content[*i + 1]) \
	&& tk->content[*i + 1] != '$' && (tk->content[*i + 1] != '?' \
	&& tk->content[*i + 1] != '_'))
		return (1);
	return (0);
}

static int	is_empty_quote(t_token *tk, int *i)
{
	if (tk->content[*i] && tk->content[*i] == '$' && tk->content[*i + 1] \
	&& tk->content[*i + 1] == '\'')
		return (1);
	else if (tk->content[*i] && tk->content[*i] == '$' && tk->content[*i + 1] \
	&& tk->content[*i + 1] == '"')
		return (1);
	return (0);
}

static void	expander_while_loop(t_ms *ms, t_token *tk, int i)
{
	while (tk && tk->content && *tk->content && tk->content[i])
	{
		if (tk->content[i] && tk->content[i] == '$' && tk->squote == 0)
		{
			if (expand_pid_exit_code_and_dollar_quoted(ms, tk, &i))
				;
			else if (is_empty_quote(tk, &i))
			{
				if (expand_empty_quote(tk, &i))
					continue ;
				else
					break ;
			}
			else if (tk->content[i] && !tk->content[i + 1])
				break ;
			else if (is_invalid_identifier(tk, &i))
				skip_invalid_identifier(tk, &i);
			else
				expand_var(ms, tk, &i);
			tk->expanded = 2;
		}
		if (*tk->content && tk->content[i])
			i++;
	}
}

void	expander(t_ms *ms, t_token *tk, int i)
{
	if (!tk)
		return ;
	while (tk)
	{
		i = 0;
		expander_while_loop(ms, tk, i);
		tk = tk->next;
	}
	remove_empty_nodes(ms->token_lexed, ms->token_lexed, NULL);
}
