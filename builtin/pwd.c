/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:18 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/04 15:40:45 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_ms **lst)
{
	char	*path;

	(*lst)->exit_code = 0;
	path = getcwd(NULL, 4096);
	if (!path)
		return ((*lst)->exit_code);
	ft_printf("%s\n", path);
	free(path);
	return ((*lst)->exit_code);
}
