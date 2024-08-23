/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/23 13:32:15 by niabraha         ###   ########.fr       */
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
1. heredoc
2. commande
3. redirection ou pipe

 */

static void simple_command(t_ms *ms)
{
	pid_t	pid;
	int		status;

	status = 0;
	printf("simple commandrtfguyhbjomk,ld\n");
	if (ms->token[0]->type == BUILTIN)
		find_builtin(ms, ms->token[0]); // changer les 0 et 1 en i
	else
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Fork error\n");
			exit(1);
		}
		if (pid == 0)
			ft_execlp(ms, cmd_to_tab(ms, ms->token[0]));
		waitpid(pid, &status, 0);
	}
	ms->exit_code = WEXITSTATUS(status);
}

int	exec_main(t_ms *ms)
{
	if (ms->heredoc_count)
		manage_heredoc(ms);
	if (ms->pipe_count > 0)
		create_pipe(ms);
	else
		simple_command(ms);
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