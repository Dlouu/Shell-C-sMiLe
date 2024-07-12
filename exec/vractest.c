/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vractest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:37:25 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/12 17:13:27 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//mon main de test

void is_builtin(t_test **test)
{
	if (ft_strncmp((*test)->content, "cd", 2) == 0) 
		(*test)->builtin = 1;
	else if (ft_strncmp((*test)->content, "echo", 4) == 0)
		(*test)->builtin = 1;
	else if (ft_strncmp((*test)->content, "env", 3) == 0)
		(*test)->builtin = 1;
	else if (ft_strncmp((*test)->content, "pwd", 3) == 0)
		(*test)->builtin = 1;
	else if (ft_strncmp((*test)->content, "export", 6) == 0)
		(*test)->builtin = 1;
	else if (ft_strncmp((*test)->content, "unset", 5) == 0)
		(*test)->builtin = 1;
	else if (ft_strncmp((*test)->content, "exit", 4) == 0)
		(*test)->builtin = 1;
	else
		(*test)->builtin = 0;
}

static void	create_head(t_test *head, char **argv)
{
	head->content = argv[1];
	is_builtin(&head);
	head->next = NULL;
	head->size = 1;
}

t_test	*create_list(int argc, char **argv)
{
	t_test	*head;
	t_test	*temp;
	int		i;

	i = 1;
	head = (t_test *)malloc(sizeof(t_test));
	if (!head)
		return (NULL);
	create_head(head, argv);
	temp = head;
	while (++i < argc)
	{
		temp->next = (t_test *)malloc(sizeof(t_test));
		if (!temp->next)
			return(free_lst(&head), NULL);
		temp = temp->next;
		temp->content = argv[i];
		is_builtin(&temp);
		temp->next = NULL;
	}
	return (head);
}

/* static void print_lst(t_test *head)
{
	t_test *temp;

	temp = head;
	while (temp)
	{
		ft_printf("temp->contentt = %s\n", temp->content);
		ft_printf("temp->builtinn = %d\n", temp->builtin);
		temp = temp->next;
	}
} */

void print_env(t_env *env)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		ft_printf("temp->key = %s\n", temp->key);
		ft_printf("temp->value = %s\n", temp->value);
		temp = temp->next;
	}
}

t_env	*free_env(t_env **env)
{
	t_env *temp;

	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp);
	}
	return (NULL);
}

t_env	*create_env(char **envp)
{
	t_env	*head;
	t_env	*temp;
	int		i;

	i = 0;
	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->key = envp[i];
	head->value = envp[i];
	head->next = NULL;
	temp = head;
	while (envp[++i])
	{
		temp->next = (t_env *)malloc(sizeof(t_env));
		if (!temp->next)
			return(free_env(&head), NULL);
		temp = temp->next;
		temp->key = envp[i];
		temp->value = envp[i];
		temp->next = NULL;
	}
	return (head);
}

int main(int argc, char **argv, char **envp)
{
	t_test *test;
	t_env 	*env;

	test = create_list(argc, argv);
	env = create_env(envp);
	print_env(env);
	find_builtin(&test, envp);
}