/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:54:49 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/12 14:52:22 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/* static void	first_child_process(t_pipex fd, char **cmd, t_ms *ms)
{
	if (dup2(fd.pipefd[1], STDOUT_FILENO) < 0)
	{
		close(fd.pipefd[0]);
		close(fd.pipefd[1]);
		printf("dup2 error1\n");
	}
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	ft_execlp(ms, cmd);
}

static void second_child_process(t_pipex fd, char **cmd, t_ms *ms)
{
	if (dup2(fd.pipefd[0], STDIN_FILENO) < 0)
	{
		close(fd.pipefd[0]);
		close(fd.pipefd[1]);
		printf("dup2 error2\n");
	}
	close(fd.pipefd[0]);
	close(fd.pipefd[1]);
	ft_execlp(ms, cmd);
}

static void parent_process(t_pipex *fd)
{
	close(fd->pipefd[0]);
	close(fd->pipefd[1]);
	waitpid(fd->pid[0], &(fd->status), 0);
	waitpid(fd->pid[1], &(fd->status), 0);
}

int exec_pipe(t_ms *ms, t_pipex *px)
{
	t_pipex fd;
	t_token	**tk_lst;
	char **cmd1;
	char **cmd2;

	(void)px;
	tk_lst = ms->token;
	cmd1 = cmd_to_tab(ms, tk_lst[ms->current_pipe]);
	cmd2 = cmd_to_tab(ms, tk_lst[ms->current_pipe + 1]);
	ms->current_pipe++;
    if (pipe(fd.pipefd) == -1)
        printf("Pipe error\n");
    fd.pid[0] = fork();
    if (fd.pid[0] < 0)
        printf("Fork error on pid[0]\n");
    if (fd.pid[0] == 0)
        first_child_process(fd, cmd1, ms);
    fd.pid[1] = fork();
    if (fd.pid[1] < 0)
        printf("Fork error on pid[1]\n");
    if (fd.pid[1] == 0)
        second_child_process(fd, cmd2, ms);
    parent_process(&fd);
    if (WIFEXITED(fd.status))
        return WEXITSTATUS(fd.status);
    return (0);
} */
