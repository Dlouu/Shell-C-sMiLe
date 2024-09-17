/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/17 16:47:24 by niabraha         ###   ########.fr       */
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

etape par etape:
1. heredoc (ouvrir les fichiers ^^)
2. commande
3. redirection ou pipe
 */

/* static void	ft_close_fds(t_pipex *px)
{
	if (px->fd_in != STDIN_FILENO)
	{
		close(px->fd_in);
		px->fd_in = STDIN_FILENO;
	}
	if (px->fd_out != STDOUT_FILENO)
	{
		close(px->fd_out);
		px->fd_out = STDOUT_FILENO;
	}
} */

/* static void ft_close_pipe(int *pipe)
{
	if (pipe[0] != -1)
		close(pipe[0]);
	if (pipe[1] != -1)
		close(pipe[1]);
}

static void ft_close_fds(t_pipex *px)
{
	if (!px)
		return ;
	if (px->pipefd[0] != 0)
		close(px->pipefd[0]);
	if (px->pipefd[1] != 1)
		close(px->pipefd[1]);
	printf("exec_first_processus\n");
}

static void exec_first_processus(t_ms *ms, t_pipex *px, t_token *tk)
{
	open_and_dup(px, tk, ms);
	if (dup2(px->pipefd[1], STDOUT_FILENO) == -1)
		exit(1); // a changer
	ft_close_fds(px);
	ft_close_pipe(px->heredoc);
	if (tk->type == BUILTIN)
		find_builtin(ms, tk);
	else
		ft_execlp(ms, cmd_to_tab(ms, tk));
}

static void exec_middle_processus(t_ms *ms, t_pipex *px, t_token *tk)
{
	open_and_dup(px, tk, ms);
	if (dup2(px->prev->pipefd[0], STDIN_FILENO) == -1 && px->heredoc[0] == -1)
		exit(1); // a changer
	if (dup2(px->pipefd[1], STDOUT_FILENO) == -1)
		exit(1); // a changer
	ft_close_fds(px);
	ft_close_fds(px->prev);
	ft_close_pipe(px->heredoc);
	if (tk->type == BUILTIN)
		find_builtin(ms, tk);
	else
		ft_execlp(ms, cmd_to_tab(ms, tk));
}

static void exec_last_processus(t_ms *ms, t_pipex *px, t_token *tk)
{
	open_and_dup(px, tk, ms);
	if (dup2(px->prev->pipefd[0], STDIN_FILENO) == -1 && px->prev)
		exit(1); // a changer
	ft_close_fds(px->prev);
	ft_close_pipe(px->heredoc);
	if (tk->type == BUILTIN)
		find_builtin(ms, tk);
	else
		ft_execlp(ms, cmd_to_tab(ms, tk));
}

static void exec_processus(t_ms *ms, t_pipex *px, t_token *tk, int i)
{
	if (i == 0)
		exec_first_processus(ms, px, tk); // pas de pipe, un seul processus
	else if (i == ms->pipe_count)
		exec_last_processus(ms, px, tk); // dernier processus
	else
		exec_middle_processus(ms, px, tk); // tous les processus du milieu
} */

static void simple_command(t_ms *ms, t_pipex *px, t_token *tk)
{
	open_and_dup(ms->px, tk, ms);
	printf("simple_command\n");
	px->pid = fork();
	if (px->pid == -1)
		exit(1); // a changer
	if (px->pid == 0)
		ft_execlp(ms, cmd_to_tab(ms, tk));
}

static void	ft_exec(t_ms *ms, t_pipex *px, t_token *tk)
{
	int 	i;

	i = 0;
	printf("pipe_count = %d\n", ms->pipe_count);
	if (tk->type == BUILTIN && ms->pipe_count == 0)
		find_builtin(ms, tk);
	if (tk->type == COMMAND && ms->pipe_count == 0)
		simple_command(ms, px, tk);
	// while (px)
	// {
	// 	px->pid = fork();
	// 	if (px->pid == -1)
	// 		exit(1); // a changer
	// 	if (px->pid == 0)
	// 		exec_processus(ms, px, tk, i);
	// 	if (px->prev)
	// 		close(px->prev->pipefd[0]);
	// 	px = px->next;
	// 	i++;
	// }
}

static int lst_size_pipe(t_pipex *px)
{
	int i;

	i = 0;
	while (px)
	{
		px = px->next;
		i++;
	}
	return (i);
}

int	exec_main(t_ms *ms)
{
	t_pipex	*px;
	t_pipex	*tmp;
	t_token	*tk;

	px = setup_pipe(ms);
	int len = lst_size_pipe(px);
	tmp = px;
	printf("len = %d\n", len);
	tk = ms->token_lexed;
	ft_exec(ms, px, tk);
	while(tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		tmp = tmp->next;
	}
	return (0);

/*	if (ms->pipe_count)
	{
		exec_pipe(ms, &px, tk);
		//simple_command(ms);
	if (ms->heredoc_count)
		manage_heredoc(ms);
	//set_redirections(ms);
	if (ms->pipe_count > 0)
		create_pipe(ms);
	else
		simple_command(ms);*/
	//exec_command(ms, &px, tk);
	//if (ms->pipe_count)
		//exec_pipe(ms, &px);
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
/*

ft_exec -> (1) preparer les pipes, (2) faire l'exec, (3) fermer les pid
(2) -> juste un builtin, pas de pipe ni commande, redir accept2 ^^
*/
	/*
	tmpier si les redir en first fonctionnent ?(creent des fichiers)
	> ls ; < oui 
	*/