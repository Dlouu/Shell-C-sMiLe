/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:23 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/09/24 16:02:40 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		if (i != 0 && prompt[i - 1] && ft_issplitable(prompt[i - 1]))
			ms->blank_before_quote = 1;
		while (prompt[i] && !ft_isseparator(prompt[i]))
		{
			if ((prompt[i] && prompt[i] == '$' \
			&& prompt[i + 1] && prompt[i + 2] \
			&& ((prompt[i + 1] == '\'' && prompt[i + 2] == '\'') \
			|| (prompt[i + 1] == '\"' && prompt[i + 2] == '\"'))))
			{
				ms->dollar = 1;
				if (prompt[i + 1] && !ft_isseparator(prompt[i + 1]))
					ms->blank_after_quote = 0;
				i += 3;
				return (i);
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
// 			if (prompt[i + 1] && (ft_issplitable(prompt[i + 1]) 
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
// 			if (prompt[i] && prompt[i] != '$' && prompt[i + 1] 
//			&& (prompt[i + 1] == '$' || prompt[i + 1] == '?'))
// 				ms->blank_after_quote = 0;
// 			if (prompt[i + 1] && (ft_issplitable(prompt[i + 1]) 
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
	if (check_unclosed_quote(prompt) != 0)
		return (error_parsing(ms, "unclosed quote"));
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
