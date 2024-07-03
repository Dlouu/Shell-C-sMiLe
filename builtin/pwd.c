/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:18 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/03 13:55:30 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_ms **lst)
{
	char	*path;

	if ((*lst)->next == NULL)
	{
		(*lst)->exit_code = 0;
		path = getcwd(NULL, 4096);
		if (!path)
			return ((*lst)->exit_code);
		ft_printf("%s\n", path);
		free(path);
	}
	else
	{
		(*lst)->exit_code = 1;
		error_message("pwd: too many arguments", (*lst)->exit_code);
	}
	return ((*lst)->exit_code);
}
