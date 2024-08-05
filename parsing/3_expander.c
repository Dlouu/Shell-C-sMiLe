/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:06:12 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/05 17:40:34 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_var_name(char *key, t_token *tk, int *i)
{
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - *i - ft_strlen(key) - 1;
	left = ft_substr(tk->content, 0, *i, FALSE);
	right = ft_substr(tk->content, *i + ft_strlen(key) + 1, len, FALSE);
	tk->content = ft_strjoin(left, right, FALSE);
	*i += ft_strlen(key) - 1;
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
		len = 50;
		left = ft_substr(tk->content, 0, *i, FALSE);
		value = find_env_value(ms->env, key);
		right = ft_substr(tk->content, *i + ft_strlen(key) + 1, len, FALSE);
		tk->content = ft_strjoin(left, value, FALSE);
		tk->content = ft_strjoin(tk->content, right, FALSE);
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
	right = ft_substr(tk->content, *i + 1, len, FALSE);
	tk->content = ft_strjoin(left, pid, FALSE);
	tk->content = ft_strjoin(tk->content, right, FALSE);
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
	*i += ft_strlen(exit_code) - 2;
}

void	expander(t_ms *ms, t_token *tk, int i)
{
	while (tk)
	{
		i = 0;
		while (tk->content[i])
		{
			if (tk->content[i] == '$' && tk->squote == 0)
			{
				if (!tk->content[i + 1])
					break ;
				else if (tk->content[i + 1] == '?')
					expand_exit_code(ms, tk, &i);
				else if (tk->content[i + 1] == '$')
					expand_pid_number(tk, &i);
				else
					expand_var(ms, tk, &i);
			}
			i++;
		}
		tk = tk->next;
	}
}
