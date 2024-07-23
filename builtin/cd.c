/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 02:27:09 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(t_test **lst)
{
	char	*old_path_to_env;

	(*lst)->exit_code = 0;
	old_path_to_env = getcwd(NULL, 4096);
	if (!old_path_to_env)
		return ((*lst)->exit_code);
	printf("old_path = %s\n", old_path_to_env);
	return ((*lst)->exit_code);
}

// /* notes :
// cd /
// cd ///////
// cd = cd ~
// cd uvbhjn = no such file or directory
// cd ..
// cd .
// cd
// cd ~
// cd e/abc/e/abc = relative path
// cd e/abc = absolute path
// cd split sur les paths et lster un par un les dossiers
// //setenv("PWD", path_max, 1); ? utile ou pas ?
// */
