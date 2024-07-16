/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:18:23 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/16 17:36:45 by mbaumgar         ###   ########.fr       */
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

// void	lexer(t_ms *ms, char *prompt, int argc, char **argv)
// {
// 	t_token	*token_lst;
// 	t_token	*new;
// 	int		i;

// 	token_lst = NULL;
// 	new = NULL;
// 	while (prompt[i])
// 	{
// 		while (isblank(prompt[i]))
// 			i++;
// 	}
// 	new = tk_lstnew(prompt);
// 	tk_lstadd(&token_lst, new);
// }
