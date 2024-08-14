/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:04 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/14 16:23:39 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cd(t_ms *ms)
{
	char *old_path;
	char *new_path;

	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (printf("old_path unset je crois\n"), 1); // vérifier le message d'erreur
	if (!ms->token_lexed->next || ft_strcmp(ms->token_lexed->next->content, "~") == 0)
	{
		if (chdir(getenv("HOME")) == -1)
			return (printf("cd: HOME not set\n"), 1);
	}
	else if (chdir(ms->token_lexed->next->content) == -1)
		return (printf("minishell: cd: %s: No such file or directory\n", ms->token_lexed->next->content), 1);
	printf("ms->token_lexed->next->content = %s\n", ms->token_lexed->next->content);
	replace_value(ms->env, "OLDPWD", old_path);
	new_path = getcwd(NULL, 0);
	replace_value(ms->env, "PWD", new_path);
	return (0);
}
/* 
marche pas
cd /////
cd ".."
 */

