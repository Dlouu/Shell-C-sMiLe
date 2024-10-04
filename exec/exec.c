/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/04 11:52:59 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
ls -l > oui | cat < oui | echo bite > non

ls -l > infile > outfile > infile (outfile vide mais infile remplie) good

grep "login.sh" < infile > outfile (outfile recupere le grep) good

grep "Videos" < infile | cat -e > outfile good

tr a-z A-Z > first_file << oui | tr A-Z a-z > second_file << non
*/

/*Voir avec Theo en auoi c'etait important de unlink avant execve*/
// static void	unlink_ptr_for_execve(char *path, char **cmd, char **envp)
// {
// 	int	i;

// 	i = -1;
// 	wunlink(path);
// 	while (cmd && cmd[++i])
// 		wunlink(cmd[i]);
// 	wunlink(cmd);
// 	i = -1;
// 	while (envp && envp[++i])
// 		wunlink(envp[i]);
// 	wunlink(envp);
// }

void	manage_execve(t_pipex *px, char **cmd, char **envp)
{
	char	*cmd_path;

	if (px->token->type == BUILTIN)
		find_builtin(px, px->token);
	cmd_path = find_path(cmd[0], envp, px->ms);
	if ((!cmd_path || (!px->token->content[0] && !px->token->expanded)) && \
	cmd[0])
		return (ft_error(cmd[0], "command not found", 1, 127));
	if (!px->token->content[0] && px->token->expanded == 2)
		clean_exit(0, NULL);
	//unlink_ptr_for_execve(cmd_path, cmd, envp);
	//wclear(1);
	if (cmd)
	{
		if (execve(cmd_path, cmd, envp) == -1)
			ft_perror("execve error", 1);
	}
}

void	ft_exec(t_pipex *px)
{
	t_pipex	*tmp;
	int		i;

	if (px->ms->pipe_count == 0 && px->token->type == BUILTIN && !px->next)
		return (find_builtin(px, px->token));
	tmp = px;
	i = 0;
	while (px && px->token)
	{
		px->pid = fork();
		if (px->pid == -1)
			ft_perror("Fork creation failed", 1);
		if (px->pid == 0)
			exec_sub_processus(px, i);
		i++;
		px = px->next;
	}
	ft_close_fds(tmp);
}

int	exec_main(t_ms *ms)
{
	t_pipex	*px;
	t_pipex	*tmp;
	int		exit_status;

	exit_status = 0;
	px = setup_pipe(ms);
	tmp = px;
	ft_exec(px);
	while (tmp)
	{
		waitpid(tmp->pid, &exit_status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(exit_status))
		ms->exit_code = WEXITSTATUS(exit_status);
	else
		ms->exit_code = 1; // verifier si c'est 1
	return (ms->exit_code);
}
