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

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = walloc(sizeof(t_ms), TRUE);
	get_envp(ms, envp);
	main_test(ms, argc, argv);
	// (void)argc;
	// (void)argv;
	// while (temp->next != NULL)
	// {
	// 	printf("%s = %s\n", ((t_env *)temp->content)->key, \
	// 	((t_env *)temp->content)->value);
	// 	// ft_putstr_fd(((t_env *)ms->env->content)->key, 1);
	// 	// ft_putstr_fd("=", 1);
	// 	// ft_putendl_fd(((t_env *)ms->env->content)->value, 1);
	// 	temp = temp->next;
	// }
    // printf("key = %s\n", ((t_env *)ms->env->content)->key);
    // printf("value = %s\n", ((t_env *)ms->env->content)->value);
    // printf("test %s\n", find_env_value(ms->env, "COLORTERM"));
    // t_list *temp = find_env_node(ms->env, "PATH");
    // printf("key = %s\n", ((t_env *)temp->content)->value);
	return (0);
}
