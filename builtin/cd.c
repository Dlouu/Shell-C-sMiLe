/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/02 18:47:01 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_path(char **envp, char *varenv)
{
	char	**all_paths;
	char	*final_path;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], varenv, 5) != 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	while (*all_paths)
	{
		final_path = getcwd(*all_paths, 4096);
		if (!final_path)
		{
			ft_printf("pas de chemin :(");
			exit(EXIT_FAILURE);
		}
		ft_printf("%s\n", final_path);
	}
	i = -1;
	while (all_paths[++i])
			free(all_paths[i]);
	free(all_paths);
	return (NULL);
}


/* int	ft_cd_which_arg(t_ms **lst)
{
	if ((*lst)->next->content == "..")
		ft_cd_dot_dot();
} */

int	ft_cd(t_ms **lst)
{
	char path_max[4096]; // trouver ce foutu max path
	char *path;
	if ((*lst)->next == NULL) //|| (*lst)->next->content = "~")
	{
		path = getcwd(path_max, 4096);
		if (!path)
			ft_printf("oupsi :(\n"); //add errno
		ft_printf("%s\n", path);
		(*lst)->exit_code = 0;
	}
/* 	else
		ft_cd_which_arg(&lst); */
	return ((*lst)->exit_code);
}

/* notes :
cd /
cd ///////
cd = cd ~
cd uvbhjn = no such file or directory
cd ..
cd .
cd
cd ~
cd e/abc/e/abc = relative path
cd e/abc = absolute path
cd split sur les paths et lster un par un les dossiers
//setenv("PWD", path_max, 1); ? utile ou pas ?
*/