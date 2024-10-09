/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 16:02:03 by mbaumgar         ###   ########.fr       */
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
		ft_putstr_fd("🤙> ", STDOUT_FILENO);
		buff = get_next_line(STDOUT_FILENO, 0, FALSE);
		buff = ft_strtrim(buff, "\n", FALSE);
		if (g_signal == SIGQUIT)
			buff = get_next_line(STDOUT_FILENO, TRUE, FALSE);
		if (!buff || g_signal == SIGINT)
		{
			signals_heredoc(px->ms, tk);
			break ;
		}
		px->buff = ft_strdup(buff, 0);
		if (px->buff && ft_strcmp(px->buff, tk->content) == 0)
			break ;
		write(px->heredoc[1], px->buff, ft_strlen(px->buff));
		write(px->heredoc[1], "\n", 1);
	}
}

// void	manage_heredoc(t_pipex *px, t_token *tk, char *buff)
// {
// 	if (px->heredoc[0] != -1)
// 		close(px->heredoc[0]);
// 	if (px->heredoc[1] != -1)
// 		close(px->heredoc[1]);
// 	if (pipe(px->heredoc) == -1)
// 		ft_perror("pipe failed", 1);
// 	set_signals(HEREDOC);
// 	while (1)
// 	{
// 		if (g_signal == SIGINT)
// 		{
// 			printf("oblige de faire touche [Enter] pour quitter, why ?\n\n");
// 			break ;
// 		}
// 		buff = readline("> ");
// 		if (!buff)
// 		{
// 			ft_error_heredoc(tk);
// 			break ;
// 		}
// 		px->buff = ft_strdup(buff, 0);
// 		free(buff);
// 		if (px->buff && ft_strcmp(px->buff, tk->content) == 0)
// 			break ;
// 		write(px->heredoc[1], px->buff, ft_strlen(px->buff));
// 		write(px->heredoc[1], "\n", 1);
// 	}
// }

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
