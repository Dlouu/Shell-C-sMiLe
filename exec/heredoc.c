/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:56:22 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/23 12:56:34 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

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
		{
			list_heredoc[i] = ft_strdup(token->next->content, 1);
			i++;
		}
		token = token->next;
	}
	list_heredoc[i] = NULL;
	return (list_heredoc);
}
void manage_heredoc(t_ms *ms)
{
	char	**list_heredoc;
	char	buffer[BUFFER_SIZE + 1];
	int		i;
	t_token	**tk;
	int		file;
	int		bytes_read;
	int		line_start;
	int		j;

	tk = ms->token;
	list_heredoc = copy_heredoc((*tk), ms->heredoc_count);
	file = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	i = 0;
	line_start = 0;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';
		j = 0;
		while (j < bytes_read)
		{
			if (buffer[j] == '\n')
			{
				buffer[j] = '\0';
				if (ft_strcmp(buffer + line_start, list_heredoc[i]) == 0)
					i++;
				else
				{
					write(file, buffer + line_start, j - line_start);
					write(file, "\n", 1);
				}
				line_start = j + 1;
				if (i == ms->heredoc_count)
				{
					close(file);
					return;
				}
			}
			j++;
		}
		if (line_start < bytes_read)
		{
			ft_memmove(buffer, buffer + line_start, bytes_read - line_start);
			line_start = bytes_read - line_start;
		}
		else
			line_start = 0;
	}
	close(file);
}