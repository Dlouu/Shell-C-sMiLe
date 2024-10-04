/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/04 18:02:22 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	manage_heredoc(t_pipex *px, t_token *tk)
{
	char	*buff;

	if (pipe(px->heredoc) == -1)
		ft_perror("pipe failed", 1);
	set_signals(HEREDOC);
	printf("signal = HEREDOC / pid %d \n", getpid());
	while (1)
	{
		buff = readline("> ");
		if (buff && ft_strcmp(buff, tk->next->content) == 0)
			break ;
		write(px->heredoc[1], buff, ft_strlen(buff));
		write(px->heredoc[1], "\n", 1);
	}
	if (px->heredoc[0] != -1 && dup2(px->heredoc[0], 0) == -1)
		return (ft_close_fds(px), ft_perror("dup2 failed", 1));
	if (px->pipefd[1] != -1)
		close(px->pipefd[1]);
}
