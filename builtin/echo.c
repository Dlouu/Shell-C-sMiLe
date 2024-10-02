/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:06 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/02 14:36:39 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_flag_n(const char *content)
{
	int	i;

	i = 1;
	if (content[0] != '-')
		return (0);
	if (content[0] == '-' && content[1] == '\0')
		return (0);
	while (content[i] == 'n')
		i++;
	return (content[i] == '\0');
}

int	ft_echo(t_ms *ms, t_token *tk)
{
	t_token	*current;
	int		flag_n;

	current = tk;
	current = current->next;
	flag_n = 0;
	while (current && current->content)
	{
		if (!is_flag_n(current->content))
			break ;
		current = current->next;
		flag_n = 1;
	}
	while (current && current->type == ARG && current->content)
	{
		write(get_fds(ms, STDOUT_FILENO), current->content,
			ft_strlen(current->content));
		current = current->next;
		if (current && current->content)
			write(get_fds(ms, STDOUT_FILENO), " ", 1);
	}
	if (!flag_n)
		write(get_fds(ms, STDOUT_FILENO), "\n", 1);
	return (0);
}
