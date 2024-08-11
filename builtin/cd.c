/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/11 21:54:04 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// printf("arg = %d\n", ms->token_lexed->builtin);

int	ft_cd(t_ms *ms)
{
	char *old_path;
	char *new_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (printf("old_path unset je crois\n"), 1); // vérifier le message d'erreur
	if (ms->token_lexed->next && ms->token_lexed->next->next)
		return (printf("minishell: cd: too many arguments\n"), 1);
	if (!ms->token_lexed->next || ft_strcmp(ms->token_lexed->next->content, "~") == 0)
	{
		if (chdir(getenv("HOME")) == -1)
			return (printf("cd: HOME not set\n"), 1);
	}
	else if (chdir(ms->token_lexed->next->content) == -1)
		return (printf("minishell: cd: %s: No such file or directory\n", ms->token_lexed->next->content), 1);
	replace_value(ms->env, "OLDPWD", old_path);
	new_path = getcwd(NULL, 0);
	replace_value(ms->env, "PWD", new_path);
	return (0);
}
/* 
faire un getcwd --> si marche pas --> old_pat unset DONE
on change la valeur de OLDPWD
si la prochaine valeur == NULL || ~ go faire un cd avec la valeur de HOME    DONE
chdir e la valeur d'apres (on suppose que c'est un chemin, on regarde si c'est valide) DONE
si marche pas --> chemin non valide DONE
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
// cd e/abc/e/abc = relative old_pat
// cd e/abc = absolute old_pat
// cd split sur les paths et lster un par un les dossiers
// //setenv("PWD", path_max, 1); ? utile ou pas ?
// */
