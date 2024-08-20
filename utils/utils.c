/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:23:55 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/20 10:33:09 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_var_name(char *key, t_token *tk, int *i)
{
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - *i - ft_strlen(key) - 1;
	left = ft_substr(tk->content, 0, *i, FALSE);
	right = ft_substr(tk->content, *i + ft_strlen(key) + 1, len, FALSE);
	tk->content = ft_strjoin(left, right, FALSE);
	*i += ft_strlen(left) - 1;
}

char	*get_var(char *var)
{
	int		i;
	char	*key;

	i = 1;
	while (var[i] && var[i] != '$' && var[i] != '=' && !ft_issplitable(var[i]))
		i++;
	key = ft_substr(var, 1, i - 1, FALSE);
	return (key);
}

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

int	find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

void	update_index(t_token **tk)
{
	t_token	*temp;
	int		index;

	index = 0;
	while ((*tk)->next && (*tk)->next->type != PIPE)
	{
		(*tk)->index = index;
		index++;
		*tk = (*tk)->next;
	}
	if ((*tk)->next && (*tk)->next->type == PIPE)
	{
		temp = (*tk)->next;
		(*tk)->next = NULL;
		(*tk)->index = index;
		*tk = temp->next;
		(*tk)->prev = NULL;
	}
	else
	{
		(*tk)->index = index;
		*tk = (*tk)->next;
	}
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
