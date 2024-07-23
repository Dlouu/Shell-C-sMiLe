/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:15 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/24 01:13:48 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* t_list *ft_add_var(t_ms *ms)
{
	t_list	*env;
	t_token	*token;
	t_env	*new_env;

	env = ms->env;
	token = ms->token;
	while (token)
	{
		if (is_valid_key(((t_env *)env->content)->key))
		{
			if (find_env_node(env, token->content) == NULL)
			{
				ft_lstadd_back(&env, ft_lstnew(ft_strdup(token->content, FALSE), FALSE));
			}
			else if (find_env_node(env, token->content) != NULL)
			{
				ft_lstdelone(&env, wfree);
				ft_lstadd_back(&env, ft_lstnew(ft_strdup(token->content, FALSE), FALSE));
			}
			else
				ft_lstadd_back(&env, ft_lstnew(ft_strdup(token->content, FALSE), FALSE));
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(token->content, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ms->exit_code = 1;
		}
		token = token->next;
	
	}
} */


int is_valid_key(char *key)
{
	int i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_list *sort_list(t_list *lst, int (*cmp)(const char *, const char *, size_t))
{
	t_list *sorted = NULL;
	t_list *current = lst;

	while (current != NULL)
	{
		t_list *next = current->next;

		if (sorted == NULL || cmp(((t_env *)current->content)->key, ((t_env *)sorted->content)->key, ft_strlen(((t_env *)current->content)->key)) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			t_list *temp = sorted;
			while (temp->next != NULL && cmp(((t_env *)temp->next->content)->key, ((t_env *)current->content)->key, ft_strlen(((t_env *)current->content)->key)) < 0)
			{
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}
		current = next;
	}
	return sorted;
}

t_list *ft_lstdup(t_list *lst)
{
	t_list *head;
	t_list *temp;

	head = NULL;
	while (lst)
	{
		temp = ft_lstnew(ft_strdup(lst->content, FALSE), FALSE);
		((t_env *)temp->content)->key = ft_strdup(((t_env *)lst->content)->key, FALSE);
		((t_env *)temp->content)->value = ft_strdup(((t_env *)lst->content)->value, FALSE);
		if (!temp)
		{
			ft_lstclear(&head, wfree);
			return (NULL);
		}
		ft_lstadd_back(&head, temp);
		lst = lst->next;
		temp = temp->next;
	}
	return (head);
}

int	ft_export(t_ms *ms)
{
	t_list	*unsorted_env;
	t_list	*sorted_env;
	t_token **token;
	//t_list	*new_var;

	unsorted_env = ft_lstdup(ms->env);
	sorted_env = sort_list(unsorted_env, ft_strncmp);
	token = ms->token;
	//si rien apres export --> ordre alphabetique
	if (!(*token)->next)
	{
		while (sorted_env)
		{
			if (!ft_strncmp(((t_env *)sorted_env->content)->key, UNDERSCORE, \
			ft_strlen(((t_env *)sorted_env->content)->key)))
			{
				sorted_env = sorted_env->next;
				continue ;
			}
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(((t_env *)sorted_env->content)->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_env *)sorted_env->content)->value, 1);
			ft_putstr_fd("\"\n", 1);
			sorted_env = sorted_env->next;
		}
	}
/* 	else if ((*token)->next)
		new_var = ft_add_var(ms); */
	return (ms->exit_code);
}
