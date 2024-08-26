/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:36:56 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/26 15:20:08 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void exec_command(t_ms *ms, t_pipex *px, t_token *tk)
{
	pid_t	pid;
	int		status;

	status = 0;
	check_redir_nils(ms, px, tk);
	if (tk->type == BUILTIN)
		find_builtin(ms, tk);
	else if (tk->type == COMMAND) // je precise dans le doute (cf. ligne 70 exec.c)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Fork error\n"); // tout dloux le dloup
			exit(1);
		}
		if (pid == 0)
			ft_execlp(ms, cmd_to_tab(ms, tk));
		waitpid(pid, &status, 0);
	}
	ms->exit_code = WEXITSTATUS(status);
	return ;
}
