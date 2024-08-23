/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:32 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/23 13:33:10 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/* void c_redir(t_ms *ms, t_token *token)
{
	int		fd;
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIR_LEFT)
		{
			fd = open(tmp->next->content, O_RDONLY);
			if (fd < 0)
			{
				printf("minishell: %s: %s\n", tmp->next->content, strerror(errno));
				ms->exit_code = 1;
				return ;
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (tmp->type == REDIR_RIGHT)
		{
			fd = open(tmp->next->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				printf("minishell: %s: %s\n", tmp->next->content, strerror(errno));
				ms->exit_code  = 1;
				return ;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (tmp->type == REDIR_DOUBLE_RIGHT)
		{
			fd = open(tmp->next->content, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				printf("minishell: %s: %s\n", tmp->next->content, strerror(errno));
				ms->exit_code = 1;
				return ;
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
} */
