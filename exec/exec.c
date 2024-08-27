/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/27 16:42:31 by niabraha         ###   ########.fr       */
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

int	exec_main(t_ms *ms)
{
	/*
	verifier si les redir en first fonctionnent ?(creent des fichiers)
	> ls ; < oui 
	*/
	t_pipex	px;
	t_token	*tk;

	// 
	init_pipe(&px);
	tk = ms->token[ms->current_pipe];
	if (tk->type == BUILTIN || tk->type == COMMAND)
		exec_command(ms, &px, tk);
	else if (tk->type == PIPE)
		exec_pipe(ms, &px);
	
	
		//simple_command(ms);
/* 	if (ms->heredoc_count)
		manage_heredoc(ms);
	//set_redirections(ms);
	if (ms->pipe_count > 0)
		create_pipe(ms);
	else
		simple_command(ms); */
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