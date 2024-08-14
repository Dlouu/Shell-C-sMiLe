/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:24:33 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/14 22:02:14 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

/* 
heredoc + pipe
le reste c'est de gauche à droite dans chaque pipe
 */

static char **copy_heredoc(t_token *token, int nbr_heredoc)
{
	int i;
	char **list_heredoc;

	i = 0;
	list_heredoc = (char **)malloc(sizeof(char *) * (nbr_heredoc + 1));
	if (!list_heredoc)
		return (NULL);
	while (token->next)
	{
		if (ft_strcmp(token->content, "<<") == 0)
		{
			list_heredoc[i] = ft_strdup(token->next->content, 1);
			i++;
		}
		token = token->next;
	}
	return (list_heredoc);
}

static int count_heredoc(t_token *token)
{
	int nbr_heredoc;

	nbr_heredoc = 0;
	while (token->next)
	{
		if (ft_strcmp(token->content, "<<") == 0)
			nbr_heredoc++;
		token = token->next;
	}
	return (nbr_heredoc);
}

static void	manage_heredoc(t_token **token)
{
	int nbr_heredoc;
	int i;
	char **list_heredoc;
	char *line;

	nbr_heredoc = count_heredoc(*token);
	list_heredoc = copy_heredoc(*token, nbr_heredoc);
	i = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, list_heredoc[i]) == 0)
			i++;
		if (i == nbr_heredoc)
			break ;
	}
}

int exec_main(t_ms *ms, t_token **token)
{
	(void)ms;
	manage_heredoc(token);
	return (0);
}
