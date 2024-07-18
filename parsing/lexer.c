/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:23 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/18 11:12:24 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/typedefs.h"

int	check_nb_quote(char *prompt, int i)
{
	int	quote;

	quote = 0;
	while (prompt[++i])
	{
		if (ft_isquote(prompt[i]) == SQUOTE)
		{
			i++;
			quote++;
			while (prompt[i] && !(ft_isquote(prompt[i]) == SQUOTE))
				i++;
			if (ft_isquote(prompt[i]) == SQUOTE)
				quote--;
		}
		else if (ft_isquote(prompt[i]) == DQUOTE)
		{
			i++;
			quote++;
			while (prompt[i] && !(ft_isquote(prompt[i]) == DQUOTE))
				i++;
			if (ft_isquote(prompt[i]) == DQUOTE)
				quote--;
		}
	}
	return (quote);
}

int	check_quotes(char *prompt, int *i)
{
	if (ft_isquote(prompt[*i]) == SQUOTE)
	{
		(*i)++;
		while (prompt[*i] && (ft_isquote(prompt[*i]) != SQUOTE))
			(*i)++;
		(*i)++;
	}
	else if (ft_isquote(prompt[*i]) == DQUOTE)
	{
		(*i)++;
		while (prompt[*i] && (ft_isquote(prompt[*i]) != DQUOTE))
			(*i)++;
		(*i)++;
	}
	return (*i);
}

int	check_chevrons(char *prompt, int *i)
{
	if (ft_ischevron(prompt[*i]) == RCHEVRON)
	{
		(*i)++;
		if (prompt[*i] && ft_ischevron(prompt[*i]) == RCHEVRON)
			(*i)++;
	}
	else if (ft_ischevron(prompt[*i]) == LCHEVRON)
	{
		(*i)++;
		if (prompt[*i] && ft_ischevron(prompt[*i]) == LCHEVRON)
			(*i)++;
	}
	return (*i);
}

int	node_size(char *prompt, int i, int *start)
{
	while (prompt[i] && ft_isblank(prompt[i]))
		i++;
	if (prompt[i] == '\0')
		return (-1);
	*start = i;
	if (ft_ispipe(prompt[i]))
		i++;
	else if (ft_isquote(prompt[i]))
		check_quotes(prompt, &i);
	else if (ft_ischevron(prompt[i]))
		check_chevrons(prompt, &i);
	else
	{
		while (prompt[i] && !ft_isseparator(prompt[i]))
			i++;
	}
	return (i);
}

int	lexer(char *prompt)
{
	t_token	*token_lst;
	t_token	*new;
	char	*content;
	int		i;
	int		start;

	i = -1;
	token_lst = NULL;
	if (check_nb_quote(prompt, i) != 0)
		return (ERR_QUOTE);
	i = 0;
	while (prompt[i])
	{
		i = node_size(prompt, i, &start);
		if (i == -1)
			break ;
		content = ft_substr(prompt, start, i - start, FALSE);
		new = tk_lstnew(content);
		tk_lstadd(&token_lst, new);
	}
	tk_lstprint(token_lst);
	return (0);
}
