/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:06:12 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/05 20:16:13 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_empty_quote(t_token *tk, int *i)
{
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - *i - 3;
	left = ft_substr(tk->content, 0, *i, FALSE);
	right = ft_substr(tk->content, *i + 3, len, FALSE);
	printf("left = [%s]\n", left);
	printf("right = [%s]\n", right);
	printf("len = [%zu]\n", len);
	tk->content = ft_strjoin(left, right, FALSE);
	printf("content = [%s]\n\n", tk->content);
	tk->expanded = 2;
	if (!tk->content[*i])
		return (0);
	while (tk->content[*i])
	{
		printf("content[%d] = %c-\n", *i, tk->content[*i]);
		if (tk->content[*i] == '$')
			return (1);
		*i += 1;
	}
	printf("SORTIE EXPAND EMPTY CHAR[%d] = %c-\n", *i, tk->content[*i]);
	return (0);
}

void	expand_var(t_ms *ms, t_token *tk, int *i)
{
	char	*key;
	char	*left;
	char	*right;
	char	*value;
	size_t	len;

	key = get_var(tk->content + *i);
	if (find_env_node(ms->env, key))
	{
		len = ft_strlen(tk->content) - *i - ft_strlen(key) - 1;
		left = ft_substr(tk->content, 0, *i, FALSE);
		value = find_env_value(ms->env, key);
		right = ft_substr(tk->content, *i + ft_strlen(key) + 1, len, FALSE);
		tk->content = ft_strjoin(left, value, FALSE);
		tk->content = ft_strjoin(tk->content, right, FALSE);
		tk->expanded = 1;
		*i += ft_strlen(value) - 1;
	}
	else
		delete_var_name(key, tk, i);
}

void	expand_pid_number(t_token *tk, int *i)
{
	char	*pid;
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - *i - 2;
	left = ft_substr(tk->content, 0, *i, FALSE);
	pid = ft_itoa(getpid(), FALSE);
	right = ft_substr(tk->content, *i + 2, len, FALSE);
	tk->content = ft_strjoin(left, pid, FALSE);
	tk->content = ft_strjoin(tk->content, right, FALSE);
	tk->expanded = 1;
	*i += ft_strlen(pid) - 2;
}

void	expand_exit_code(t_ms *ms, t_token *tk, int *i)
{
	char	*exit_code;
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - *i - 2;
	left = ft_substr(tk->content, 0, *i, FALSE);
	exit_code = ft_itoa(ms->exit_code, FALSE);
	right = ft_substr(tk->content, *i + 2, len, FALSE);
	tk->content = ft_strjoin(left, exit_code, FALSE);
	tk->content = ft_strjoin(tk->content, right, FALSE);
	tk->expanded = 1;
	*i += ft_strlen(exit_code) - 2;
}

void	remove_empty_nodes(t_ms *ms)
{
	t_token	*tk;
	t_token	*temp;

	tk = ms->token_lexed;
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
				tk_delone(&ms->token_lexed, temp);
		}
		else
			tk = tk->next;
	}
}

void	skip_invalid_identifier(t_token *tk, int *i)
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
	tk_lstprint(ms, &ms->token_lexed);
	while (tk)
	{
		i = 0;
		while (tk && tk->content && tk->content[i]) // NEED HELP HERE
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
				if (tk->content[i + 1] && !ft_isalpha(tk->content[i + 1]) && \
				tk->content[i + 1] != '$' && (tk->content[i + 1] != '?' \
				&& tk->content[i + 1] != '_'))
					skip_invalid_identifier(tk, &i);
				else
					expand_var(ms, tk, &i);
				tk->expanded = 2;
			}
			i++;
		}
		tk = tk->next;
	}
	tk_lstprint(ms, &ms->token_lexed);
	remove_empty_nodes(ms);
}
