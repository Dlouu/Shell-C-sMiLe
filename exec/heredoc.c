/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/04 16:58:12 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void do_heredoc(t_pipex *px, t_ms *ms, char **copy)
{
	char *line;

	if (px->fd_in != STDIN_FILENO) // redir
		close(px->fd_in);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO, 0, 0);
		if (!line)
			break ;
		line = ft_strtrim(line, "\n", 0);
		if (ft_strlen(line) == ft_strlen(copy[ms->heredoc_count_check]))
		{
			if (ft_strncmp(line, copy[ms->heredoc_count_check], ft_strlen(line)) == 0)
				ms->heredoc_count_check++;
			if (ms->heredoc_count_check == ms->heredoc_count)
				exit(ms->exit_code); //chut c'est un secre
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

void manage_heredoc(t_ms *ms, t_pipex *px)
{
	char 	**copy;
	t_token	**tk;
	pid_t	pid;

	tk = ms->token;
	copy = copy_heredoc((*tk), ms->heredoc_count);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error\n");
		exit(1);
	}
	if (pid == 0)
		do_heredoc(px, ms, copy);
	else
	{
		waitpid(pid, NULL, 0);
		close(px->pipefd[1]);
		px->fd_in = dup(px->pipefd[0]);
		close(px->pipefd[0]);
		if (px->fd_in == -1)
			return ;
	}
}
