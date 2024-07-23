/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:15 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 21:29:35 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

	unsorted_env = ft_lstdup(ms->env);
	sorted_env = sort_list(unsorted_env, ft_strncmp);
	//si rien apres export --> ordre alphabetique
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
	return (ms->exit_code);
}
/* notes :
export = que pour créer
c’est unset qui delete et attention si on spécifie pas de valeur
voir avec alexis le expander “EOF” et EOF
*/
