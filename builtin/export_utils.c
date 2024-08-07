/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:15 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/07 11:33:45 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_valid_key(char *key)
{
	size_t	i;

	i = 0;
	// printf("key = %s\n", key);
	// printf("key[i] = %c\n", key[i]);
	if (key[i] && !ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i] && key[i] != '=')
	{
		// printf("key[i] = %c\n", key[i]);
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_list	*sort_list(t_list *current, t_list *sorted, int (*cmp)(const char *, \
																const char *))
{
	t_list	*temp;
	t_list	*next;

	while (current != NULL)
	{
		next = current->next;
		if (sorted == NULL || cmp(((t_env *)current->data)->key, \
		((t_env *)sorted->data)->key) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			temp = sorted;
			while (temp->next != NULL && cmp(((t_env *)temp->next->data)->key, \
			((t_env *)current->data)->key) < 0)
				temp = temp->next;
			current->next = temp->next;
			temp->next = current;
		}
		current = next;
	}
	return (sorted);
}

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*head;
	t_list	*tmp;
	t_env	*env;

	head = NULL;
	while (lst)
	{
		tmp = ft_lstnew(ft_strdup(lst->data, FALSE), FALSE);
		env = walloc(sizeof(t_env), FALSE);
		tmp->data = env;
		if (!tmp)
		{
			ft_lstclear(&head, wfree);
			return (NULL);
		}
		((t_env *)tmp->data)->key = \
		ft_strdup(((t_env *)lst->data)->key, FALSE);
		((t_env *)tmp->data)->value = \
		ft_strdup(((t_env *)lst->data)->value, FALSE);
		ft_lstadd_back(&head, tmp);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (head);
}

void	ft_putstr_export(char *key, char *value)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(key, 1);
	if (value[0] != 26)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}
