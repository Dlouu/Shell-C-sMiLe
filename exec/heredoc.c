/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/29 21:17:50 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void do_heredoc(t_pipex *px, char **copy)
{
	char *line;
	
	if (px->fd_in != STDIN_FILENO)
		close(px->fd_in);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO, 0, 0);
		if (!line)
			break ;
		line = ft_strtrim(line, "\n", 0);
		if (ft_strlen(line) == ft_strlen(copy[px->ms->i]))
		{
			if (ft_strncmp(line, copy[px->ms->i], ft_strlen(line)) == 0)
				px->ms->i++;
			if (px->ms->i == px->ms->heredoc_count)
				exit(px->ms->exit_code); //chut c'est un secret
		}
		write(px->pipefd[1], line, ft_strlen(line));
		write(px->pipefd[1], "\n", 1);
		free(line);
	}
	close(px->pipefd[1]);
}

static char	**copy_heredoc(t_token *token, int nbr_heredoc)
{
	int		i;
	char	**list_heredoc;

	i = 0;
	list_heredoc = (char **)walloc(sizeof(char *) * (nbr_heredoc + 1), FALSE);
	if (!list_heredoc)
		return (NULL);
	while (token->next)
	{
		if (token->type == REDIR_DOUBLE_LEFT)
			list_heredoc[i++] = ft_strdup(token->next->content, 1);
		token = token->next;
	}
	list_heredoc[i] = NULL;
	return (list_heredoc);
}

void manage_heredoc(t_pipex *px)
{
	char 	**copy;
	t_token	**tk;

	tk = px->ms->token;
	copy = copy_heredoc((*tk), px->ms->heredoc_count);
	if (!copy)
		ft_perror("malloc failed", 1);
	do_heredoc(px, copy);
}
