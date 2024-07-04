/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/03 17:37:59 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_env(char **envp, char *varenv)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(varenv);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], varenv, len) == 0)
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}


// /* int	ft_cd_which_arg(t_ms **lst)
// {
// 	if ((*lst)->next->content == "..")
// 		ft_cd_dot_dot();
// } */

int	ft_cd(t_ms **lst)
{
// 	char	path_max[4096]; // trouver ce foutu max path
// 	char	*home_path;

// 	if ((*lst)->next == NULL) //|| (*lst)->next->content = "~")
// 	{
// 		home_path = find_path(envp, "HOME=");
// 		if (!home_path)
// 			ft_printf("oupsi :(\n"); //add errno
// 		ft_printf("%s\n", home_path);
// 		(*lst)->exit_code = 0;
// 	}
// /* 	else
// 		ft_cd_which_arg(&lst); */
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