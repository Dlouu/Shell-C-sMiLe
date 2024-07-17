/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:23 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/17 16:36:07 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/typedefs.h"

//split
//lexer(token)
//parser (virer double pipe, redir vide, etc)
//bonne liste dans l'ordre
//expander (variable et quotes)
//nils

int	check_nb_quote(char *prompt, int i)
{
	int	quote;

	quote = 0;
	while (prompt[i++])
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

int	lexer(char *prompt)
{
	t_token	*token_lst;
	t_token	*new;
	char	*content;
	int		i;
	int		start;

	i = 0;
	token_lst = NULL;
	if (!check_nb_quote(prompt, i))
		return (ERR_QUOTE);
	while (prompt[i])
	{
		while (prompt[i] && ft_isblank(prompt[i]))
			i++;
		start = i;
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
		content = ft_substr(prompt, start, i - start, FALSE);
		new = tk_lstnew(content);
		tk_lstadd(&token_lst, new);
	}
	printf("token_lst:\n");
	i = 1;
	while (token_lst)
	{
		printf("content #%d: %s\n", i, token_lst->content);
		token_lst = token_lst->next;
		i++;
	}
	return (0);
}
