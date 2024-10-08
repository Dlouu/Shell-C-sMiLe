/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/08 14:40:08 by mbaumgar         ###   ########.fr       */
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

static void	ft_error_heredoc(t_pipex *px, t_token *tk)
{
	ft_close_everything(px);
	if (g_signal == SIGINT)
		clean_exit(130, NULL);
	else
		ft_error("warning: here-document delimited by EOF wanted",
			tk->content, 0, 1);
}

void	manage_heredoc(t_pipex *px, t_token *tk)
{
	char	*buff;

	if (px->heredoc[0] != -1)
		close(px->heredoc[0]);
	if (px->heredoc[1] != -1)
		close(px->heredoc[1]);
	if (pipe(px->heredoc) == -1)
		ft_perror("pipe failed", 1);
	set_signals(HEREDOC);
	while (1)
	{
		buff = readline("> ");
		if (!buff)
			ft_error_heredoc(px, tk);
		px->buff = ft_strdup(buff, 0);
		free(buff);
		if (px->buff && ft_strcmp(px->buff, tk->content) == 0)
			break ;
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
				manage_heredoc(px, tk);
			tk = tk->next;
		}
		px = px->next;
	}
}
