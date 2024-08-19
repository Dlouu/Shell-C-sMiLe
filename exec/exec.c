/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/19 16:01:37 by niabraha         ###   ########.fr       */
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

static void manage_pipe(t_ms *ms)
{
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
			if (tk->type == PIPE)
			{
				// fork
				// exec
				// waitpid
			}
			tk = tk->next;
		}
		i++;
	}
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

int	exec_main(t_ms *ms)
{
	(void)ms;

	manage_pipe(ms);
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