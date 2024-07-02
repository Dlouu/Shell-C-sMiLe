/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vractest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:37:25 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/02 19:50:26 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//mon main de test

void is_builtin(t_ms **test)
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

static void	create_head(t_ms *head, char **argv)
{
	head->content = argv[1];
	is_builtin(&head);
	head->next = NULL;
}

t_ms	*create_list(int argc, char **argv)
{
	t_ms	*head;
	t_ms	*temp;
	int		i;

	i = 2;
	head = (t_ms *)malloc(sizeof(t_ms));
	if (!head)
		return (NULL);
	create_head(head, argv);
	temp = head;
	while (i < argc)
	{
		temp->next = (t_ms *)malloc(sizeof(t_ms));
		if (!temp->next)
			return(free_lst(&head), NULL);
		temp = temp->next;
		temp->content = argv[i];
		is_builtin(&temp);
		temp->next = NULL;
		i++;
	}
	return (head);

}

/* static void print_lst(t_ms *head)
{
	t_ms *temp;

	temp = head;
	while (temp)
	{
		ft_printf("temp->contentt = %s\n", temp->content);
		ft_printf("temp->builtinn = %d\n", temp->builtin);
		temp = temp->next;
	}
} */

int main(int argc, char **argv, char **envp)
{
	t_ms *test;

	test = create_list(argc, argv);
	//print_lst(test);
	find_builtin(&test, envp);
}