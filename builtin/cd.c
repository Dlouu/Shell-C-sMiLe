/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/07 18:31:38 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(t_ms *ms)
{
/* 	char *path;

	path = getcwd(NULL, 0);
	if (!path)
		return (printf("path unset je crois\n"), 1); */
	return (0);
}
/* 
faire un getcwd --> si marche pas --> path unset
on change la valeur de OLDPWD
si la prochaine valeur == NULL || ~ go faire un cd avec la valeur de HOME
chdir e la valeur d'apres (on suppose que c'est un chemin, on regarde si c'est valide)
si marche pas --> chemin non valide
on change la valeur de PWD
 */

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
