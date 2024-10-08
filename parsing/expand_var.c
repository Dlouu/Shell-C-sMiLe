/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:06:12 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/08 19:30:22 by mbaumgar         ###   ########.fr       */
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
	tk->content = ft_strjoin(left, right, FALSE);
	tk->expanded = 2;
	if (!tk->content[*i])
		return (0);
	while (tk->content[*i])
	{
		if (tk->content[*i] == '$')
			return (1);
		*i += 1;
	}
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

static void	expand_pid_number(t_token *tk, int **i)
{
	char	*pid;
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - **i - 2;
	left = ft_substr(tk->content, 0, **i, FALSE);
	pid = ft_itoa(getpid(), FALSE);
	right = ft_substr(tk->content, **i + 2, len, FALSE);
	tk->content = ft_strjoin(left, pid, FALSE);
	tk->content = ft_strjoin(tk->content, right, FALSE);
	tk->expanded = 1;
	**i += ft_strlen(pid) - 2;
}

static void	expand_exit_code(t_ms *ms, t_token *tk, int **i)
{
	char	*exit_code;
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - **i - 2;
	left = ft_substr(tk->content, 0, **i, FALSE);
	exit_code = ft_itoa(ms->exit_code, FALSE);
	right = ft_substr(tk->content, **i + 2, len, FALSE);
	tk->content = ft_strjoin(left, exit_code, FALSE);
	tk->content = ft_strjoin(tk->content, right, FALSE);
	tk->expanded = 1;
	**i += ft_strlen(exit_code) - 2;
}

int	expand_pid_exit_code_and_dollar_quoted(t_ms *ms, t_token *tk, int *i)
{
	if (tk->content[*i] && tk->content[*i] == '$' && tk->content[*i + 1] \
	&& tk->content[*i + 1] == '?')
	{
		expand_exit_code(ms, tk, &i);
		return (1);
	}
	else if (tk->content[*i] && tk->content[*i] == '$' && tk->content[*i + 1] \
	&& tk->content[*i + 1] == '$')
	{
		expand_pid_number(tk, &i);
		return (1);
	}
	else if (tk->next && (tk->next->squote || tk->next->dquote) \
	&& tk->content[0] == '$' && !tk->content[*i + 1])
	{
		tk_delone(&ms->token_lexed, tk);
		(*i)++;
		return (1);
	}
	return (0);
}
