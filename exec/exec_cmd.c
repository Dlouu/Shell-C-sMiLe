/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:54:36 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 02:24:31 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	find_builtin(t_ms *ms, t_test **test)
{
	if (ft_strncmp((*test)->content, "cd", 2) == 0)
		ft_cd(test);
	else if (ft_strncmp((*test)->content, "echo", 4) == 0)
		ft_echo(test);
	else if (ft_strncmp((*test)->content, "env", 3) == 0)
		ft_env(ms);
	else if (ft_strncmp((*test)->content, "pwd", 3) == 0)
		ft_pwd(test);
	else if (ft_strncmp((*test)->content, "export", 6) == 0)
		ft_export(ms);
	else if (ft_strncmp((*test)->content, "unset", 5) == 0)
		ft_unset(ms, test);
	else if (ft_strncmp((*test)->content, "exit", 4) == 0)
		(*test)->builtin = 1;
	else
		(*test)->builtin = 0;
}

/* notes :
Builtin pwd, env echo en first (conseil de Max)

toutes les fonctions doivent renvoyer un INT
il faut check les valeurts de retour

echo $PWD (copie de pwd donc faut pas l'use)
(les utiliser une fois au lancement et en faire une copie)
*/
