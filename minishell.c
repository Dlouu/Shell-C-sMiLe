/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/15 16:47:47 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = walloc(sizeof(t_ms), TRUE);
	get_envp(ms, envp);
	main_test(ms, argc, argv);
	// (void)argc;
	// (void)argv;
	// t_token	*token_lst;
	// t_token *new;
	// token_lst = NULL;
	// new = tk_lstnew("test");
	// tk_lstadd(&token_lst, new);
	// printf("token->content: %s\n", new->content);
	return (0);
}
