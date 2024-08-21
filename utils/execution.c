/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:50:11 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/21 15:23:39 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**env_lst_to_tab(t_ms *ms)
{
	t_list	*env;
	char	**envp;
	int		i;
	char	*key;

	env = ms->env;
	i = 0;
	envp = walloc(sizeof(char *) * (ft_lstsize(env) + 1), FALSE);
	while (env)
	{
		if (((t_env *)env->data)->value)
		{
			key = ft_strjoin(((t_env *)env->data)->key, "=", FALSE);
			envp[i] = ft_strjoin(key, ((t_env *)env->data)->value, FALSE);
		}
		else
			envp[i] = ft_strdup(((t_env *)env->data)->key, FALSE);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	**cmd_to_tab(t_ms *ms, t_token *tk)
{
	char	**cmd;
	int		i;
	int		size;
	t_token	*temp;

	i = 0;
	size = 0;
	temp = tk;
	(void)ms;
	while (temp)
	{
		if (temp->type == COMMAND || temp->type == BUILTIN || temp->type == ARG)
			size++;
		temp = temp->next;
	}
	cmd = walloc(sizeof(char *) * (size + 1), FALSE);
	while (i < size)
	{
		cmd[i] = ft_strdup(tk->content, FALSE);
		tk = tk->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}
