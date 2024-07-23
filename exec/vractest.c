/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vractest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:37:25 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 06:14:06 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//mon main de test

/* void is_builtin(t_test **test)
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
} */

/* static void	create_head(t_test *head, char **argv)
{
	head->content = argv[1];
	is_builtin(&head);
	head->next = NULL;
	head->size = 1;
} */

/* t_test	*create_list(int argc, char **argv)
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
} */

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


/* int main_test(t_ms *ms, int argc, char **argv)
{
	t_test *test;

	test = create_list(argc, argv);
	find_builtin(ms, &test);
	return (0);
} */

