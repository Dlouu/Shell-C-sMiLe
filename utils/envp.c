/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:32:45 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/09 11:35:30 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//if the user has not set a value for the key, the value will be set to 26
//26 is the "substitute" character in ascii table
//this is done to avoid setting the value to NULL
//in ft_env and ft_putstr_export functions, we will check if the value is 26
//if it is, we will not print the value

void	replace_env_value(t_list *env, char *key, char *value)
{
	t_list	*tmp;

	tmp = find_env_node(env, key);
	if (tmp)
	{
		wfree(((t_env *)tmp->data)->value);
		((t_env *)tmp->data)->value = ft_strdup(value, TRUE);
	}
}

void	add_env_node(t_ms *ms, char *key_and_value)
{
	int		equals;
	int		len;
	t_list	*new;
	t_env	*new_env;

	len = ft_strlen(key_and_value);
	equals = find_index(key_and_value, '=');
	if (equals == -1)
	{
		new_env = (t_env *)walloc(sizeof(t_env), TRUE);
		new_env->key = ft_substr(key_and_value, 0, len, TRUE);
		new_env->value = ft_substr("", 0, 0, TRUE);
		new_env->value[0] = 26;
	}
	else
	{
		new_env = (t_env *)walloc(sizeof(t_env), TRUE);
		new_env->key = ft_substr(key_and_value, 0, equals, TRUE);
		new_env->value = ft_substr(key_and_value, equals + 1, len, TRUE);
	}
	new = ft_lstnew(new_env, TRUE);
	ft_lstadd_back(&ms->env, new);
}

t_list	*find_env_node(t_list *env, char *key)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->data)->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*find_env_value(t_list *env, char *key)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(((t_env *)tmp->data)->key, key) == 0)
			return (((t_env *)tmp->data)->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list	*get_envp(t_ms *ms, char **envp)
{
	int		i;

	ms->env = (t_list *)walloc(sizeof(t_list), TRUE);
	ms->env = NULL;
	i = 0;
	while (envp[i])
	{
		add_env_node(ms, envp[i]);
		i++;
	}
	return (ms->env);
}
