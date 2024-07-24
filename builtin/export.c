/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:15 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/24 04:53:52 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Faire un sas pour traiter differemment les VAR_ENV et VAR_EXPORT
//si VAR_ENV on met juste le nom de la var
//si VAR_EXPORT on met le nom de la var et la valeur
//si y'a un egal il faut mettre ="" sinon juste le nom de la var (key)
//export caca != export caca="" != caca=""

int	is_valid_key(char *key)
{
	size_t	i;

	i = 0;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalpha(key[i]) && key[i] != '_')
			return (0);
		i++;
		while (key[i] && key[i] != '=')
		{
			if (!ft_isalnum(key[i]) && key[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

//a check plus tard
//ca duplique plutot que de modifier
//check la facon dont est cast la t_env ou t_list si c'est ok
//si y'a un egal il faut mettre ="" sinon juste le nom de la var (key)
//export nom sans egal = liste de VAR (s'affiche dans export mais pas dans env)
//meme comportement pour zzz=zzzz sans export devant
int	*ft_add_var(t_ms *ms)
{
	t_list	*env;
	t_token	**token;
	t_list	*new_env;
	int		equals;
	int		len;

	env = ms->env;
	token = NULL;
	token = ms->token;
	*token = (*ms->token)->next;
	while (token && *token)
	{
		if (is_valid_key((*token)->content))
		{
			if (find_env_node(env, (*token)->content) != NULL)
			{
				len = ft_strlen((*token)->content);
				new_env = find_env_node(env, (*token)->content);
				wfree(((t_env *)new_env->content)->value);
				equals = find_index((*token)->content, '=');
				((t_env *)new_env->content)->value = ft_substr((*token)->content, equals + 1, len, TRUE);
			}
			else
				add_env_node(ms, (*token)->content);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd((*token)->content, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ms->exit_code = 1;
		}
		*token = (*token)->next;
	}
	return (&ms->exit_code);
}

t_list	*sort_list(t_list *lst, int (*cmp)(const char *, const char *, size_t))
{
	t_list	*sorted = NULL;
	t_list	*current = lst;

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
	else
		ft_add_var(ms);
	return (ms->exit_code);
}
