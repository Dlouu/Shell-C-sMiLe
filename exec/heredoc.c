/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/04 18:39:24 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_heredoc(t_pipex *px, t_token *tk)
{
	if (pipe(px->heredoc) == -1)
		ft_perror("pipe failed", 1);
	set_signals(HEREDOC);
	printf("signal = HEREDOC / pid %d \n", getpid());
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		px->buff = get_next_line(STDIN_FILENO, 0, FALSE);
		px->buff = ft_strtrim(px->buff, "\n", FALSE);
		if (px->buff && ft_strcmp(px->buff, tk->next->content) == 0)
			break ;
		write(px->heredoc[1], px->buff, ft_strlen(px->buff));
		write(px->heredoc[1], "\n", 1);
	}
	if (px->heredoc[0] != -1 && dup2(px->heredoc[0], 0) == -1)
		return (ft_close_fds(px), ft_perror("dup2 failed", 1));
	if (px->heredoc[0] != -1)
		close(px->heredoc[0]);
	if (px->heredoc[1] != -1)
		close(px->heredoc[1]);
}
