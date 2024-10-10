/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/10 16:27:37 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*find_my_token(t_pipex *px, int type)
{
	t_token	*tk;

	tk = px->token;
	while (tk)
	{
		if (tk->type == type)
			return (tk);
		tk = tk->next;
	}
	return (NULL);
}

static void	signals_heredoc(t_ms *ms, t_token *tk)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		ms->exit_code = 130;
		ms->dont_touch = 1;
	}
	else
	{
		ft_putstr_fd("\nminishell: warning: here-document ", STDERR_FILENO);
		ft_putstr_fd("delimited by EOF wanted: ", STDERR_FILENO);
		ft_putendl_fd(tk->content, STDERR_FILENO);
		ms->exit_code = 0;
	}
}

void	delete_heredoc_var_name(char *key, t_pipex *px, int *i)
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
	char	*left;
	char	*right;
	char	*value;
	size_t	len;

	key = NULL;
	while (i > -1 && px && px->buff && *px->buff && px->buff[i])
	{
		if (px->buff[i] == '$')
		{
			key = get_var(px->buff + i);
			if (find_env_node(px->ms->env, key) && \
			find_env_value(px->ms->env, key) != NULL)
			{
				len = ft_strlen(px->buff) - i - ft_strlen(key) - 1;
				left = ft_substr(px->buff, 0, i, TRUE);
				value = find_env_value(px->ms->env, key);
				right = ft_substr(px->buff, i + ft_strlen(key) + 1, len, TRUE);
				px->buff = ft_strjoin(left, value, TRUE);
				px->buff = ft_strjoin(px->buff, right, TRUE);
				i += ft_strlen(value) - 1;
			}
			else
				delete_heredoc_var_name(key, px, &i);
		}
		if (i > -1 && px && px->buff && *px->buff && px->buff[i])
			i++;
	}
}

void	manage_heredoc(t_pipex *px, t_token *tk, char *buff)
{
	if (px->heredoc[0] != -1)
		close(px->heredoc[0]);
	if (px->heredoc[1] != -1)
		close(px->heredoc[1]);
	if (pipe(px->heredoc) == -1)
		ft_perror("pipe failed", 1);
	set_signals(HEREDOC);
	while (1)
	{
		ft_putstr_fd("🤙 > ", STDOUT_FILENO);
		buff = get_next_line(STDOUT_FILENO, 0, TRUE);
		buff = ft_strtrim(buff, "\n", TRUE);
		if (g_signal == SIGQUIT)
			buff = get_next_line(STDOUT_FILENO, TRUE, TRUE);
		if (!buff || g_signal == SIGINT)
		{
			signals_heredoc(px->ms, tk);
			break ;
		}
		px->buff = ft_strdup(buff, 0);
		if (px->buff && ft_strcmp(px->buff, tk->content) == 0)
			break ;
		if (tk->content && tk->squote != 1 && tk->dquote != 1)
			expand_heredoc(px, 0);
		write(px->heredoc[1], px->buff, ft_strlen(px->buff));
		write(px->heredoc[1], "\n", 1);
	}
}

void	init_heredoc(t_pipex *px)
{
	t_token	*tk;

	if (!px)
		return ;
	while (px)
	{
		tk = find_my_token(px, DELIMITER);
		while (tk)
		{
			if (tk->type == DELIMITER)
				manage_heredoc(px, tk, NULL);
			tk = tk->next;
		}
		px = px->next;
	}
}
