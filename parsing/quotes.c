/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:23:55 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/09/24 16:02:24 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	go_to_next_quote(char *prompt, int *i, int *quote, int quote_type)
{
	(*i)++;
	(*quote)++;
	while (prompt[*i] && !(ft_isquote(prompt[*i]) == quote_type))
		(*i)++;
	if (ft_isquote(prompt[*i]) == quote_type)
		(*quote)--;
}

int	check_unclosed_quote(char *prompt)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (prompt[i])
	{
		if (ft_isquote(prompt[i]) == SQUOTE)
			go_to_next_quote(prompt, &i, &quote, SQUOTE);
		else if (ft_isquote(prompt[i]) == DQUOTE)
			go_to_next_quote(prompt, &i, &quote, DQUOTE);
		if (prompt[i])
			i++;
	}
	return (quote);
}

int	check_quotes(t_ms *ms, char *prompt, int *i)
{
	if (ft_isquote(prompt[*i]) == SQUOTE)
	{
		if (*i != 0 && prompt[(*i) - 1] \
		&& ft_issplitable(prompt[(*i) - 1]) == 1)
			ms->blank_before_quote = 1;
		(*i)++;
		while (prompt[*i] && (ft_isquote(prompt[*i]) != SQUOTE))
			(*i)++;
		(*i)++;
		if (ft_issplitable(prompt[*i]) == 1 || prompt[*i] == '\0')
			ms->blank_after_quote = 1;
	}
	else if (ft_isquote(prompt[*i]) == DQUOTE)
	{
		if (*i != 0 && prompt[(*i) - 1] \
		&& ft_issplitable(prompt[(*i) - 1]) == 1)
			ms->blank_before_quote = 1;
		(*i)++;
		while (prompt[*i] && (ft_isquote(prompt[*i]) != DQUOTE))
			(*i)++;
		(*i)++;
		if (ft_issplitable(prompt[*i]) == 1 || prompt[*i] == '\0')
			ms->blank_after_quote = 1;
	}
	return (*i);
}
