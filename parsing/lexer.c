/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:23 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/25 05:07:57 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	check_quotes(t_ms *ms, char *prompt, int *i)
{
	if (ft_isquote(prompt[*i]) == SQUOTE)
	{
		(*i)++;
		while (prompt[*i] && (ft_isquote(prompt[*i]) != SQUOTE))
			(*i)++;
		(*i)++;
		if (ft_issplitable(prompt[*i]) == 1 || prompt[*i] == '\0')
			ms->blank_after_quote = 1;
	}
	else if (ft_isquote(prompt[*i]) == DQUOTE)
	{
		(*i)++;
		while (prompt[*i] && (ft_isquote(prompt[*i]) != DQUOTE))
			(*i)++;
		(*i)++;
		if (ft_issplitable(prompt[*i]) == 1 || prompt[*i] == '\0')
			ms->blank_after_quote = 1;
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

int	node_size(t_ms *ms, char *prompt, int i, int *start)
{
	while (prompt[i] && ft_isblank(prompt[i]))
		i++;
	if (prompt[i] == '\0')
		return (-1);
	*start = i;
	if (ft_ispipe(prompt[i]))
		i++;
	else if (ft_isquote(prompt[i]))
		check_quotes(ms, prompt, &i);
	else if (ft_ischevron(prompt[i]))
		check_chevrons(prompt, &i);
	else
	{
		while (prompt[i] && !ft_isseparator(prompt[i]))
			i++;
	}
	return (i);
}

int	lexer(t_ms *ms, char *prompt)
{
	t_token	*token_lst;
	t_token	*new;
	char	*content;
	int		i;
	int		start;

	i = -1;
	token_lst = NULL;
	if (check_nb_quote(prompt, i) != 0)
		return (error_quote(ms, prompt));
	i = 0;
	while (prompt[i])
	{
		i = node_size(ms, prompt, i, &start);
		if (i == -1)
			break ;
		content = ft_substr(prompt, start, i - start, FALSE);
		new = tk_lstnew(content);
		new->blank_after_quote = ms->blank_after_quote;
		ms->blank_after_quote = 0;
		tk_lstadd(&token_lst, new);
	}
	ms->token_lexed = token_lst;
	return (1);
}
