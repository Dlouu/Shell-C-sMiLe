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
	wfree(final_path);
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

//dlou : au fait que veux dire execlp ?
static void	ft_execlp(t_ms *ms, char *cmd, char **envp)
{
	char	*path;
	char	**tab;

	tab = ft_split(cmd, ' ', FALSE);
	path = find_path(tab[0], envp);
	if (!path)
	{
		ft_putstr_fd("shell-C-smile: ", 2);
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ms->exit_code = 127;
	}
	else
		execve(path, tab, envp);
}

//dlou: j'ai changé le path que tu avais déclaré dans un char*
// en ms->path dans la structure
// je sais plus la subtilité de quand on unset ou quoi
// mais apparemment quand on lance un shell dans un shell faut mettre un path
// par defaut

//dlou : ATTENTION FAUT UTILISER STRCMP ET PAS STRNCMP car si on a un echo2
// ou echonyayayay ça va faire echo j'ai add strcmp dans la lib et changé ici
void	find_builtin(t_ms *ms, t_token **token, char **envp)
{
	ms->path = find_env_value(ms->env, "PATH");
	if (ft_strcmp((*token)->content, "cd") == 0)
		ft_cd(ms);
	else if (ft_strcmp((*token)->content, "echo") == 0)
		ft_echo(ms);
	else if (ft_strcmp((*token)->content, "env") == 0)
		ft_env(ms);
	else if (ft_strcmp((*token)->content, "pwd") == 0)
		ft_pwd(ms);
	else if (ft_strcmp((*token)->content, "export") == 0)
		ft_export(ms);
	else if (ft_strcmp((*token)->content, "unset") == 0)
		ft_unset(ms);
	else if (ft_strcmp((*token)->content, "exit") == 0)
		ft_exit(ms);
	else
		ft_execlp(ms, (*token)->content, envp);
}

/* notes :
Builtin pwd, env echo en first (conseil de Max)

toutes les fonctions doivent renvoyer un INT
il faut check les valeurs de retour

echo $PWD (copie de pwd donc faut pas l'use)
(les utiliser une fois au lancement et en faire une copie)
utiliser getcwd

faut check les path pour voir si ya la cmd dedans et message d'erreur
si pas dedans
*/
