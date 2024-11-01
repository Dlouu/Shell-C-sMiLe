/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:15 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/09 18:44:10 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	update_or_create_var(t_ms *ms, t_token **token)
{
	t_list	*env;
	t_list	*env_to_update;
	int		equals;
	size_t	len;
	char	*extracted_key;

	env = ms->env;
	len = ft_strlen((*token)->content);
	equals = find_index((*token)->content, '=');
	extracted_key = ft_substr((*token)->content, 0, equals, FALSE);
	if (equals == -1 && find_env_node(env, extracted_key))
		;
	else if (find_env_node(env, extracted_key) != NULL)
	{
		env_to_update = find_env_node(env, extracted_key);
		if (((t_env *)env_to_update->data)->value)
			wfree(((t_env *)env_to_update->data)->value);
		((t_env *)env_to_update->data)->value = ft_substr((*token)->content, \
		equals + 1, len, TRUE);
	}
	else
		add_env_node(ms, (*token)->content);
}

unsigned char	*ft_add_var(t_ms *ms)
{
	t_token	**token;

	token = ms->token;
	*token = (*ms->token)->next;
	while (token && *token && (*token)->type == ARG)
	{
		if (is_valid_key((*token)->content))
			update_or_create_var(ms, token);
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd((*token)->content, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ms->exit_code = 1;
			ms->dont_touch = 1;
		}
		*token = (*token)->next;
	}
	return (&ms->exit_code);
}

int	ft_export(t_ms *ms, t_token *token)
{
	t_list	*unsorted_env;
	t_list	*sorted_env;

	unsorted_env = ft_lstdup(ms->env, NULL, NULL, NULL);
	sorted_env = sort_list(unsorted_env, NULL, ft_strcmp);
	if (!token->next || (token->next->type >= REDIR_LEFT
			&& token->next->type <= REDIR_DOUBLE_RIGHT))
	{
		while (sorted_env)
		{
			if (!ft_strcmp(((t_env *)sorted_env->data)->key, UNDERSCORE))
			{
				sorted_env = sorted_env->next;
				continue ;
			}
			ft_putstr_export(ms, ((t_env *)sorted_env->data)->key, \
			(((t_env *)sorted_env->data)->value));
			sorted_env = sorted_env->next;
		}
	}
	else
		ft_add_var(ms);
	return (ms->exit_code);
}
