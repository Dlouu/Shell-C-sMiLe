/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/24 17:27:10 by niabraha         ###   ########.fr       */
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

grep "Videos" < infile | cat -e > outfile

tr a-z A-Z > first_file << oui | tr A-Z a-z > second_file << non
*/

static void print_value(t_pipex *px)
{
	if (!px && px->prev)
		px = px->prev;
	while (px && px->prev)
		px = px->prev;
	while (px)
	{
		printf("\npx->pid: %d\n", px->pid);
		printf("px->token->content: %s\n", px->token->content);
		printf("px->pipefd[0]: %d\n", px->pipefd[0]);
		printf("px->pipefd[1]: %d\n", px->pipefd[1]);
		printf("px->heredoc[0]: %d\n", px->heredoc[0]);
		printf("px->heredoc[1]: %d\n", px->heredoc[1]);
		px = px->next;
	}
}

static void ft_close_everything(t_pipex *px)			
{
	if (!px && px->prev)
		px = px->prev;
	while (px && px->prev)
		px = px->prev;
	while (px)
	{
		if (px->pipefd[0] != -1 && px->pipefd[0] != 0 && px->pipefd[0] != 1)
{			close(px->pipefd[0]);
			px->pipefd[0] = -1;}
		if (px->pipefd[1] != -1 && px->pipefd[1] != 1 && px->pipefd[1] != 0)
{			close(px->pipefd[1]);
			px->pipefd[1] = -1;}
		if (px->heredoc[0] != -1 && px->heredoc[0] != 0 && px->heredoc[0] != 1)
{			close(px->heredoc[0]);
			px->heredoc[0] = -1;}
		if (px->heredoc[1] != -1 && px->heredoc[1] != 1 && px->heredoc[1] != 0)
{			close(px->heredoc[1]);
			px->heredoc[1] = -1;}
		px = px->next;
	}
}

void	manage_execve(t_pipex *px, char **cmd, char **envp)
{
	char	*cmd_path;

	if (px->token->type == BUILTIN)
		find_builtin(px, px->token);
	cmd_path = find_path(cmd[0], envp, px->ms);
	if (!cmd_path || (!px->token->content[0] && !px->token->expanded))
		return (ft_error(cmd[0], "command not found", 1, 1));
	if (!px->token->content[0] && px->token->expanded == 2)
		exit(0);
	if (execve(cmd_path, cmd, envp) == -1)
		ft_perror("execve error", 1);
}

void	ft_exec_first_processus(t_pipex *px)
{
	char	**menvp;
	char	**cmd;

	menvp = env_lst_to_tab(px->ms);
	//open_and_dup(px, px->token, px->ms);
	printf("pid first: %d\n", getpid());
	if (dup2(px->pipefd[1], 1) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_everything(px);
	if (!px->token->content)
		exit(0);
	cmd = cmd_to_tab(px->ms, px->token);
	manage_execve(px, cmd, menvp);
}

void	ft_exec_middle_processus(t_pipex *px)
{
	char	**menvp;
	char	**cmd;

	menvp = env_lst_to_tab(px->ms);
	//open_and_dup(px, px->token, px->ms);
	printf("pid mid: %d\n", getpid());
	if (px->heredoc[0] == -1 && dup2(px->prev->pipefd[0], 0) == -1)
		ft_perror("dup2 failed", 1);
	if (dup2(px->pipefd[1], 1) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_everything(px);
	if (!px->token->content)
		exit(0);
	cmd = cmd_to_tab(px->ms, px->token);
	manage_execve(px, cmd, menvp);
}

void	ft_exec_last_processus(t_pipex *px)
{
	char	**menvp;
	char	**cmd;

	menvp = env_lst_to_tab(px->ms);
	//open_and_dup(px, px->token, px->ms);
	printf("pid last: %d\n", getpid());
	if (px->prev && dup2(px->prev->pipefd[0], 0) == -1)
		ft_perror("dup2 failed", 1);
	ft_close_everything(px);
	cmd = cmd_to_tab(px->ms, px->token);
	manage_execve(px, cmd, menvp);
}

void	exec_sub_processus(t_pipex *px, int i)
{
	if (i == px->ms->pipe_count)
		ft_exec_last_processus(px);
	else if (i == 0)
		ft_exec_first_processus(px);
	else
		ft_exec_middle_processus(px);
}

void	ft_exec(t_pipex *px)
{
	int	i;

	if (px->ms->pipe_count == 0 && px->token->type == BUILTIN)
		return (find_builtin(px, px->token));
	i = 0;
	while (px && px->token)
	{
		px->pid = fork();
		if (px->pid == -1)
			ft_perror("Fork creation failed", 1);
		if (px->pid == 0)
			exec_sub_processus(px, i); // le gosse
		i++;
		px = px->next;
	}
}

int	exec_main(t_ms *ms)
{
	t_pipex	*px;
	t_pipex	*tmp;
	t_pipex *bite;

	px = setup_pipe(ms);
	tmp = px;
	bite = px;
	ft_exec(px);
	while(tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	print_value(bite);
	printf("pid main: %d\n", getpid());
	ft_close_everything(px);
	print_value(bite);
	return (0);
}
