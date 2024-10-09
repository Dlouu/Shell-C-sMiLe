/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:57:32 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 17:05:22 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	to_do_heredoc_or_not_to_do(t_pipex *px, int fdin)
{
	t_token	*tk;
	int		check;

	tk = find_my_token(px, DELIMITER);
	if (!tk)
		return (0);
	check = 0;
	while (tk)
	{
		if (tk->type == DELIMITER)
			check = 0;
		else if (tk->type == REDIR_LEFT)
			check = 1;
		tk = tk->next;
	}
	if (check)
		return (0);
	if (fdin != -1)
		close(fdin);
	if (dup2(px->heredoc[0], STDIN_FILENO) == -1)
		return (ft_close_everything(px), ft_perror("dup2 failed", 1), 1);
	return (1);
}

static void	verif_redir(t_pipex *px, int save_in, int save_out)
{
	int	check;

	check = to_do_heredoc_or_not_to_do(px, save_in);
	if (!check && save_in != -1)
	{
		if (dup2(save_in, STDIN_FILENO) == -1)
			return (ft_perror("dup2 error\n", 1));
		if (px->pipefd[0] > 0)
			close(px->pipefd[0]);
		px->pipefd[0] = save_in;
	}
	if (!check)
		close_heredoc(px);
	if (save_out != -1)
	{
		if (dup2(save_out, STDOUT_FILENO) == -1)
			return (ft_perror("dup2 error\n", 1));
		if (px->pipefd[1] != -1)
			close(px->pipefd[1]);
		px->pipefd[1] = save_out;
	}
}

static void	redir_out(char *file, int redir, int *save_out)
{
	if (*save_out != -1)
		close(*save_out);
	if (redir == REDIR_RIGHT)
		*save_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir == REDIR_DOUBLE_RIGHT)
		*save_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*save_out == -1)
		return (ft_perror("open error\n", 1));
}

static void	redir_in(char *file, int *save_in)
{
	if (access(file, F_OK) == -1)
	{
		ft_perror(file, 0);
		return ;
	}
	if (*save_in != -1)
		close(*save_in);
	*save_in = open(file, O_RDONLY);
	if (*save_in == -1)
		return (ft_perror("open error\n", 1));
}

void	open_and_dup(t_pipex *px, t_token *tk, int is_subprocess)
{
	int	save_in;
	int	save_out;

	save_in = -1;
	save_out = -1;
	while (tk)
	{
		if (tk->type == REDIR_LEFT)
			redir_in(tk->next->content, &save_in);
		else if (tk->type == REDIR_RIGHT || tk->type == REDIR_DOUBLE_RIGHT)
			redir_out(tk->next->content, tk->type, &save_out);
		tk = tk->next;
	}
	if (is_subprocess)
		verif_redir(px, save_in, save_out);
	else
	{
		px->ms->fds_builtins[0] = save_in;
		px->ms->fds_builtins[1] = save_out;
	}
}
