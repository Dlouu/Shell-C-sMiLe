/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:54:36 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/25 16:12:45 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*check_path(char *cmd, char *path)
{
	char	*possible_path;
	char	*final_path;

	possible_path = ft_strjoin(path, "/", FALSE);
	final_path = ft_strjoin(possible_path, cmd, FALSE);
	if (access(final_path, F_OK) == 0)
		return (final_path);
	free(final_path);
	return (NULL);
}

static char	*find_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*final_path;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':', FALSE);
	i = -1;
	while (all_paths[++i])
	{
		final_path = check_path(cmd, all_paths[i]);
		if (final_path)
			return (final_path);
	}
	i = -1;
	return (NULL);
}

static void	ft_execlp(char *cmd, char **envp)
{
	char	*path;
	char	**tab;
	int		i;

	i = -1;
	tab = ft_split(cmd, ' ', FALSE);
	path = find_path(tab[0], envp);
	execve(path, tab, envp);
}

void	find_builtin(t_ms *ms, t_token **token, char **envp)
{
	char	*path;

	path = find_env_value(ms->env, "PATH");
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
		ft_execlp((*token)->content, envp);
}

/* notes :
Builtin pwd, env echo en first (conseil de Max)

toutes les fonctions doivent renvoyer un INT
il faut check les valeurts de retour

echo $PWD (copie de pwd donc faut pas l'use)
(les utiliser une fois au lancement et en faire une copie)

faut check les path pour voir si ya la cmd dedans et message d'erreur si pas dedans
*/
