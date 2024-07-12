/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:09 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/12 17:17:23 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_test **lst, char **envp)
{
	if (!envp || !*envp)
		error_message("env: environnement not found", 127);
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	(*lst)->exit_code = 0;
	return ((*lst)->exit_code);
}
