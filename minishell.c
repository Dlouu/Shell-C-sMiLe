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

// int	find_index(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] != c)
// 		i++;
// 	return (i);
// }

// void	lstdelone_env(t_env *env, void (*del)(void *))
// {
// 	if (!env || !del)
// 		return ;
// 	(*del)(env->key);
// 	(*del)(env->value);
// 	wfree(env);
// }

// void	lstadd_env(t_env **env, t_env *new)
// {
// 	new->next = *env;
// 	*env = new;
// }

// t_env	*lstnew_env(char *key, char *value)
// {
// 	t_env	*new;

// 	new = (t_env *)walloc(sizeof(t_env), TRUE);
// 	if (!new)
// 		return (NULL);
// 	new->key = key;
// 	new->value = value;
// 	new->next = NULL;
// 	return (new);
// }

// t_env	*get_envv(t_ms *ms, char **env)
// {
// 	t_env	*env_lst;
// 	int		i;
// 	int		equals;
// 	int		len;
// 	t_env	*new;

// 	env_lst = (t_env *)walloc(sizeof(t_env), TRUE);
// 	i = 0;
// 	while (env[i])
// 	{
// 		len = ft_strlen(env[i]);
// 		equals = find_index(env[i], '=');
// 		new = lstnew_env(ft_substr(env[i], 0, equals, TRUE), \
// 		ft_substr(env[i], equals + 1, len, TRUE));
// 		lstadd_env(&env_lst, new);
// 		i++;
// 	}
// 	return (*env);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	t_ms	*ms;

// 	ms = walloc(sizeof(t_ms), TRUE);
// 	(void)argc;
// 	(void)argv;
// 	get_envv(ms, env);
// 	return (0);
// }
