/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:42:53 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/12 18:46:00 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

/* int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = walloc(sizeof(t_ms), TRUE);
	(void)argc;
	(void)argv;
	get_envp(ms, envp);
    printf("key = %s\n", ((t_env *)ms->env->content)->key);
    printf("value = %s\n", ((t_env *)ms->env->content)->value);
    printf("test %s\n", find_env_value(ms->env, "COLORTERM"));
    t_list *temp = find_env_node(ms->env, "PATH");
    printf("key = %s\n", ((t_env *)temp->content)->value);
	return (0);
} */
