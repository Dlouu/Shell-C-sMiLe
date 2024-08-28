/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:23 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/28 16:37:10 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_nb_quote(char *prompt)
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
	if (ft_ispipe(prompt[i])) // wtf ?
		i++;
	else if (ft_isquote(prompt[i]))
		check_quotes(ms, prompt, &i);
	else if (ft_ischevron(prompt[i]))
		check_chevrons(prompt, &i);
	else
	{
		if (i != 0 && prompt[i - 1] && ft_issplitable(prompt[i - 1]))
			ms->blank_before_quote = 1;
		while (prompt[i] && !ft_issplitable(prompt[i]))
		{
			if (prompt[i] && prompt[i] == '$')
			{
				ms->dollar = 1;
				if (prompt[i + 1] && \
				(prompt[i + 1] == '$' || prompt[i + 1] == '?'))
					i++;
				else if (prompt[i + 1] && ft_isalnum(prompt[i + 1]))
				{
					i++;
					while (prompt[i + 1] && ft_isalnum(prompt[i + 1]))
						i++;
				}
				if (ft_isalnum(prompt[i]) && prompt[i + 1] && prompt[i + 1] == '$')
				{
					printf("prompt[i]: %c\n", prompt[i]);
					ms->blank_after_quote = 0;
					return (i);
				}
				// if (prompt[i + 1] && prompt[i + 1] == '$')
				// {
				// 	i++;
				// 	ms->blank_after_quote = 0;
				// 	return (i);
				// }
			}
			if (prompt[i + 1] && (ft_issplitable(prompt[i + 1]) \
			|| prompt[i + 1] == '\0'))
				ms->blank_after_quote = 1;
			i++;
		}
	}
	return (i);
}

// int	node_size(t_ms *ms, char *prompt, int i, int *start)
// {
// 	while (prompt[i] && ft_isblank(prompt[i]))
// 		i++;
// 	if (prompt[i] == '\0')
// 		return (-1);
// 	*start = i;
// 	if (ft_ispipe(prompt[i]))
// 		i++;
// 	else if (ft_isquote(prompt[i]))
// 		check_quotes(ms, prompt, &i);
// 	else if (ft_ischevron(prompt[i]))
// 		check_chevrons(prompt, &i);
// 	else
// 	{
// 		if (i != 0 && prompt[i - 1] && ft_issplitable(prompt[i - 1]))
// 			ms->blank_before_quote = 1;
// 		while (prompt[i] && !ft_isseparator(prompt[i]))
// 		{
// 			if (prompt[i + 1] && (ft_issplitable(prompt[i + 1]) \
// 			|| prompt[i + 1] == '\0'))
// 				ms->blank_after_quote = 1;
// 			i++;
// 		}
// 	}
// 	return (i);
// }

// int	node_size(t_ms *ms, char *prompt, int i, int *start)
// {
// 	while (prompt[i] && ft_isblank(prompt[i]))
// 		i++;
// 	if (prompt[i] == '\0')
// 		return (-1);
// 	*start = i;
// 	if (ft_ispipe(prompt[i]))
// 		i++;
// 	else if (ft_isquote(prompt[i]))
// 		check_quotes(ms, prompt, &i);
// 	else if (ft_ischevron(prompt[i]))
// 		check_chevrons(prompt, &i);
// 	else
// 	{
// 		if (i != 0 && prompt[i - 1] && ft_issplitable(prompt[i - 1]))
// 			ms->blank_before_quote = 1;
// 		while (prompt[i] && !ft_isseparator(prompt[i]))
// 		{
// 			if (prompt[i] && prompt[i] == '$')
// 			{
// 				printf("prompt[i]: %c\n", prompt[i]);
// 				if (prompt[i + 1] && prompt[i + 1] == '$')
// 				{
// 					if (prompt[i + 2] && prompt[i + 2] == '$')
// 					{
// 						ms->dollar = 1;
// 						ms->blank_after_quote = 0;
// 						i++;
// 						i++;
// 						return (i);
// 					}
// 					else
// 					{
// 						ms->blank_after_quote = 1;
// 						i++;
// 						i++;
// 						return (i);
// 					}
// 				}
// 				else if (prompt[i + 1] && prompt[i + 1] == '?')
// 				{
// 					if (prompt[i + 2] && prompt[i + 2] == '$')
// 					{
// 						ms->dollar = 1;
// 						ms->blank_after_quote = 0;
// 						i++;
// 						i++;
// 						return (i);
// 					}
// 					else
// 					{
// 						ms->blank_after_quote = 1;
// 						i++;
// 						i++;
// 						return (i);
// 					}
// 				}
// 				i++;
// 				return (i);
// 			}
// 			if (prompt[i] && prompt[i] != '$' && prompt[i + 1] \
//			&& (prompt[i + 1] == '$' || prompt[i + 1] == '?'))
// 				ms->blank_after_quote = 0;
// 			if (prompt[i + 1] && (ft_issplitable(prompt[i + 1]) \
// 			|| prompt[i + 1] == '\0'))
// 				ms->blank_after_quote = 1;
// 			i++;
// 		}
// 	}
// 	return (i);
// }

int	lexer(t_ms *ms, char *prompt, t_token *token_lst)
{
	t_token	*new;
	char	*content;
	int		i;
	int		start;

	i = 0;
	if (check_nb_quote(prompt) != 0)
		return (error_free_prompt(ms, prompt, "unclosed quote"));
	while (prompt[i])
	{
		i = node_size(ms, prompt, i, &start);
		if (i == -1)
			break ;
		content = ft_substr(prompt, start, i - start, FALSE);
		new = tk_lstnew(content);
		new->blank_before_quote = ms->blank_before_quote;
		new->blank_after_quote = ms->blank_after_quote;
		new->dollar = ms->dollar;
		ms->blank_before_quote = 0;
		ms->blank_after_quote = 0;
		ms->dollar = 0;
		tk_lstadd(&token_lst, new);
	}
	ms->token_lexed = token_lst;
	return (1);
}
