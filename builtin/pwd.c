/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:18 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/08 15:58:22 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_ms *ms)
{
	char	*path;

	ms->exit_code = 0;
	path = getcwd(NULL, 4096);
	if (!path)
		return (ms->exit_code);
	ft_putendl_fd(path, get_fds(ms, STDOUT_FILENO));
	free(path);
	return (ms->exit_code);
}
