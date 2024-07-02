/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:18 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/02 19:28:12 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_ms **lst)
{
	char path_max[4096]; // trouver ce foutu max path  //interdit vla
	char *path;
	if ((*lst)->next == NULL)
	{
		path = getcwd(path_max, 4096);
		ft_printf("%s\n", path);
		(*lst)->exit_code = 0;
	}
	else
	{
		(*lst)->exit_code = 1;
		error_message("pwd: too many arguments", (*lst)->exit_code);
	}
	return ((*lst)->exit_code);
}