/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/06 18:53:29 by niabraha         ###   ########.fr       */
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

void	manage_heredoc(t_pipex *px, t_token *tk)
{
	if (px->heredoc[0] != -1)
		close(px->heredoc[0]);
	if (px->heredoc[1] != -1)
		close(px->heredoc[1]);
	if (pipe(px->heredoc) == -1)
		ft_perror("pipe failed", 1);
	set_signals(HEREDOC);
	//printf("signal = HEREDOC / pid %d \n", getpid());
/* 	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		px->buff = get_next_line(STDIN_FILENO, 0, FALSE);
		px->buff = ft_strtrim(px->buff, "\n", FALSE);
		// printf("buff = %s\n", px->buff);
		// printf("tk->content = %s\n", tk->content);
		if (px->buff && ft_strcmp(px->buff, tk->content) == 0)
			break ;
			write(px->heredoc[1], px->buff, ft_strlen(px->buff));
			write(px->heredoc[1], "\n", 1);
		} */
	while (1)
	{
		px->buff = readline("> ");
		if (px->buff && ft_strcmp(px->buff, tk->content) == 0)
			break ;
		write(px->heredoc[1], px->buff, ft_strlen(px->buff));
		write(px->heredoc[1], "\n", 1);
		free(px->buff);
	}
	free(px->buff);
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
