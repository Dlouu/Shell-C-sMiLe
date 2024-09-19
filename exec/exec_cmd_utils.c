/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:54:36 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/19 17:17:37 by tclaereb         ###   ########.fr       */
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
	return (NULL);
}

char	*find_path(char *cmd, char **envp, t_ms *ms)
{
	char	**all_paths;
	char	*final_path;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	if (!find_env_value(ms->env, "PATH"))
		return (NULL);
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

void	ft_execlp(t_ms *ms, char **cmd)
{
	char	*path;
	char	**envp;

	envp = env_lst_to_tab(ms);
	path = find_path(cmd[0], envp, ms);
	if (!path)
	{
		ms->exit_code = 127;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		// fonction qui clean tout
		exit(ms->exit_code);
	}
	else
	{
		if (execve(path, cmd, envp) == -1)
		{
			ms->exit_code = 126;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": permission denied\n", 2);
			exit(ms->exit_code);
		}
	}
}

//dlou: j'ai changé le path que tu avais déclaré dans un char*
// en ms->path dans la structure
// je sais plus la subtilité de quand on unset ou quoi
// mais apparemment quand on lance un shell dans un shell faut mettre un path
// par defaut
void	find_builtin(t_pipex *px, t_token *token)
{
	px->ms->path = find_env_value(px->ms->env, "PATH");
	if (ft_strcmp(token->content, "cd") == 0)
		ft_cd(px->ms, token);
	else if (ft_strcmp(token->content, "echo") == 0)
		ft_echo(px->ms, token);
	else if (ft_strcmp(token->content, "env") == 0)
		ft_env(px->ms);
	else if (ft_strcmp(token->content, "pwd") == 0)
		ft_pwd(px->ms);
	else if (ft_strcmp(token->content, "export") == 0)
		ft_export(px->ms, token);
	else if (ft_strcmp(token->content, "unset") == 0)
		ft_unset(px->ms, token);
	else if (ft_strcmp(token->content, "exit") == 0)
		ft_exit(px->ms, token);
	if (px->pid == 0)
		exit(0);
	// else
	// 	ft_execlp(ms, cmd_to_tab(ms,token);
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
