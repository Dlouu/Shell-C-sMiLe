/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:32:45 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/25 05:07:01 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	del_env_node(t_list **env, char *key)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			wfree(((t_env *)tmp->content)->key);
			wfree(((t_env *)tmp->content)->value);
			wfree(tmp->content);
			wfree(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
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
	new_env = (t_env *)walloc(sizeof(t_env), TRUE);
	new_env->key = ft_substr(key_and_value, 0, equals, TRUE);
	new_env->value = ft_substr(key_and_value, equals + 1, len, TRUE);
	new = ft_lstnew(new_env, TRUE);
	ft_lstadd_back(&ms->env, new);
}

int	env_node_exist(t_list *env, char *key)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->key, key, ft_strlen(key)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_list	*find_env_node(t_list *env, char *key)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(((t_env *)tmp->content)->key, key, ft_strlen(key)) == 0)
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
		if (ft_strncmp(((t_env *)tmp->content)->key, key, ft_strlen(key)) == 0)
			return (((t_env *)tmp->content)->value);
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

// t_list	*get_envp(t_ms *ms, char **envp)
// {
// 	int		i;
// 	int		equals;
// 	int		len;
// 	t_list	*new;
// 	t_env	*new_env;

// 	ms->env = (t_list *)walloc(sizeof(t_list), TRUE);
// 	ms->env = NULL;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		len = ft_strlen(envp[i]);
// 		equals = find_index(envp[i], '=');
// 		new_env = (t_env *)walloc(sizeof(t_env), TRUE);
// 		new_env->key = ft_substr(envp[i], 0, equals, TRUE);
// 		new_env->value = ft_substr(envp[i], equals + 1, len, TRUE);
// 		new = ft_lstnew(new_env, TRUE);
// 		ft_lstadd_back(&ms->env, new);
// 		i++;
// 	}
// 	return (ms->env);
// }
