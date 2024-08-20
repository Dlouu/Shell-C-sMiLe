/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/20 15:44:30 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* 
heredoc + pipe
le reste c'est de gauche à droite dans chaque pipe
- il ne faut pas utiliser readline pour les heredoc
- il faut utiliser GNL pour les heredoc
- j'ai fait token->type == REDIR_DOUBLE_LEFT pour les heredoc
- il n'y a pas besoin de faire de strcmp
- quand tu fais un malloc il faut utiliser 'walloc'
- quand tu uses free c'est 'wfree' mais c'est pas obligatoire de free car on 
  free tout automatiquement à la fin de chaque boucle
*/

/* 
ls -l > oui | cat < oui | echo bite > non

ls -l > infile > outfile > infile (outfile vide mais infile remplie)

grep "login.sh" < infile > outfile (outfile recupere le grep)

grep "Videos" < infile | cat



tr a-z A-Z > first_file << oui | tr A-Z a-z > second_file << non
 */

static void	first_child_process(t_pipex fd, char **cmd, t_ms *ms)
{
	if (dup2(fd.pipefd[1], STDOUT_FILENO) < 0)
	{
		close(fd.pipefd[0]);
		close(fd.pipefd[1]);
		printf("dup2 error\n");
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
		printf("dup2 error\n");
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

static int create_pipe(t_ms *ms)
{
	t_pipex fd;
	t_token	**tk_lst;
	char **cmd1;
	char **cmd2;

	tk_lst = ms->token;
	cmd1 = cmd_to_tab(ms, tk_lst[ms->current_pipe]);
	cmd2 = cmd_to_tab(ms, tk_lst[ms->current_pipe + 1]);
	ms->current_pipe += 1;
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
		{
			list_heredoc[i] = ft_strdup(token->next->content, 1);
			i++;
		}
		token = token->next;
	}
	list_heredoc[i] = NULL;
	return (list_heredoc);
}

static void	manage_heredoc(t_ms *ms)
{
	char	**list_heredoc;
	char	*line;
	int		i;
	t_token	**tk;

	tk = ms->token;
	list_heredoc = copy_heredoc((*tk), ms->heredoc_count);
	i = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, list_heredoc[i]) == 0)
			i++;
		if (i == ms->heredoc_count)
			break ;
	}
}

static void simple_command(t_ms *ms)
{
	pid_t	pid;
	int		status;

	printf("no pipe\n");
	pid = fork();
	if (pid < 0)
	{
		printf("Fork error\n");
		exit(1);
	}
	if (pid == 0)
	{
		if (ms->token[0]->type == BUILTIN)
			find_builtin(ms, ms->token[0]); // changer les 0 et 1 en i
		else
			ft_execlp(ms, cmd_to_tab(ms, ms->token[0]));
	}
	waitpid(pid, &status, 0);	
	ms->exit_code = WEXITSTATUS(status);
}

int	exec_main(t_ms *ms)
{
	if (ms->pipe_count)
		create_pipe(ms);
	else
		simple_command(ms);
	if (ms->heredoc_count)
		manage_heredoc(ms);
	return (0);
}
/*

echo f=| f=ls f=| echo  = 3 fork
echo f=| echo f=| echo  = 2 fork
f=ls f=| f=ls f=| f=ls = 5 fork

pipe = 1 fork
command = 1 fork
builtin = 0 fork

pour iterer dans les pipes :

	t_token	**tk_lst;
	t_token	*tk;
	int		i;

	tk_lst = ms->token;
	i = 0;
	while (tk_lst[i])
	{
		tk = tk_lst[i];
		while (tk->next)
		{
			BLAH
			tk = tk->next;
		}
		i++;
	}

*/