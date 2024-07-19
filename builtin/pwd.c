/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:18 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/12 23:24:17 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_test **lst)
{
	char	*path;

	(*lst)->exit_code = 0;
	path = getcwd(NULL, 4096);
	if (!path)
		return ((*lst)->exit_code);
	write(1, path, ft_strlen(path));
	free(path);
	return ((*lst)->exit_code);
}
