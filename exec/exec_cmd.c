/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:54:36 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 06:15:07 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	find_builtin(t_ms *ms, t_token **token)
{
	if (ft_strncmp((*token)->content, "cd", 2) == 0)
		ft_cd(ms);
	else if (ft_strncmp((*token)->content, "echo", 4) == 0)
		ft_echo(ms);
	else if (ft_strncmp((*token)->content, "env", 3) == 0)
		ft_env(ms);
	else if (ft_strncmp((*token)->content, "pwd", 3) == 0)
		ft_pwd(ms);
	else if (ft_strncmp((*token)->content, "export", 6) == 0)
		ft_export(ms);
	else if (ft_strncmp((*token)->content, "unset", 5) == 0)
		ft_unset(ms);
	else if (ft_strncmp((*token)->content, "exit", 4) == 0)
		ft_exit(ms);
	else
		(*token)->builtin = 0;
}

/* notes :
Builtin pwd, env echo en first (conseil de Max)

toutes les fonctions doivent renvoyer un INT
il faut check les valeurts de retour

echo $PWD (copie de pwd donc faut pas l'use)
(les utiliser une fois au lancement et en faire une copie)
*/
