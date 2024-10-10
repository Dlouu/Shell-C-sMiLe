/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:33:24 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/10 17:01:52 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	expand_heredoc_pid(t_pipex *px, int *i)
{
	char	*pid;
	char	*left;
	char	*right;
	size_t	len;

	pid = ft_itoa(getpid(), TRUE);
	len = ft_strlen(px->buff) - *i - 2;
	left = ft_substr(px->buff, 0, *i, TRUE);
	right = ft_substr(px->buff, *i + 2, len, TRUE);
	px->buff = ft_strjoin(left, pid, TRUE);
	px->buff = ft_strjoin(px->buff, right, TRUE);
	*i += ft_strlen(pid) - 1;
}

static void	expand_heredoc_exit_code(t_pipex *px, int *i)
{
	char	*exit_code;
	char	*left;
	char	*right;
	size_t	len;

	exit_code = ft_itoa(px->ms->exit_code, TRUE);
	len = ft_strlen(px->buff) - *i - 2;
	left = ft_substr(px->buff, 0, *i, TRUE);
	right = ft_substr(px->buff, *i + 2, len, TRUE);
	px->buff = ft_strjoin(left, exit_code, TRUE);
	px->buff = ft_strjoin(px->buff, right, TRUE);
	*i += ft_strlen(exit_code) - 1;
}

static void	expand_heredoc_var_name(char *key, t_pipex *px, int *i)
{
	char	*left;
	char	*right;
	char	*value;
	size_t	len;

	len = ft_strlen(px->buff) - *i - ft_strlen(key) - 1;
	left = ft_substr(px->buff, 0, *i, TRUE);
	value = find_env_value(px->ms->env, key);
	right = ft_substr(px->buff, *i + ft_strlen(key) + 1, len, TRUE);
	px->buff = ft_strjoin(left, value, TRUE);
	px->buff = ft_strjoin(px->buff, right, TRUE);
	*i += ft_strlen(value) - 1;
}

static void	delete_heredoc_var_name(char *key, t_pipex *px, int *i)
{
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(px->buff) - *i - ft_strlen(key) - 1;
	left = ft_substr(px->buff, 0, *i, TRUE);
	right = ft_substr(px->buff, *i + ft_strlen(key) + 1, len, TRUE);
	px->buff = ft_strjoin(left, right, TRUE);
	*i -= 1;
}

void	expand_heredoc(t_pipex *px, int i)
{
	char	*key;

	key = NULL;
	while (i > -1 && px && px->buff && *px->buff && px->buff[i])
	{
		if (px->buff[i] == '$')
		{
			if (px->buff[i + 1] == '$')
				expand_heredoc_pid(px, &i);
			else if (px->buff[i + 1] == '?')
				expand_heredoc_exit_code(px, &i);
			else
			{
				key = get_var(px->buff + i);
				if (find_env_node(px->ms->env, key) && \
				find_env_value(px->ms->env, key) != NULL)
					expand_heredoc_var_name(key, px, &i);
				else
					delete_heredoc_var_name(key, px, &i);
			}
		}
		if (i > -1 && px && px->buff && *px->buff && px->buff[i])
			i++;
	}
}
