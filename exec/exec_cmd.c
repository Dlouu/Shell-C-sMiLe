/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:36:56 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/28 16:29:16 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void exec_command(t_ms *ms, t_pipex *px, t_token *tk)
{
	pid_t	pid;
	int		status;

	status = 0;
	open_and_dup(px, tk, ms);
	if (tk->type == BUILTIN)
		find_builtin(ms, tk);
	else if (tk->type == COMMAND) // je precise dans le doute (cf. ligne 70 exec.c)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Fork error\n"); // tout dloux le dloup
			exit(1);
		}
		if (pid == 0)
			ft_execlp(ms, cmd_to_tab(ms, tk));
		else
			waitpid(pid, &status, 0);
	}
	
	if (dup2(px->save_out, STDOUT_FILENO) == -1)
		perror("dup2 error\n");
	if (dup2(px->save_in, STDIN_FILENO) == -1)
		perror("dup2 error\n");
	ms->exit_code = WEXITSTATUS(status);
	return ;
}

/*
fichier stocke dans une chaine
tu parcours la chaine
a chaque fichier tu open et tu attribus le fd_in ou fd_out au fd du open
si autre fichier de redirection apres tu close le fd_in actuel et tu le remplaces par le nouveau
apres tout parcouru tu dup2 si fd_in est different de STDIN_FILENO pareil pour fd_out
apres avoir execute la commande si fd_in ou fd_out est different de STDIN_FILENO ou STDOUT_FILENO tu close et tu utilses ta backup save_in ou save_out
en les dup2 au STDIN (0) et STDOUT (1) 
*/
