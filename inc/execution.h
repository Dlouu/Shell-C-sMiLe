/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:59 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/28 17:36:21 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;
	int 	save_in;
	int 	save_out;
	int		status;
	int		pipefd[2];
	int		i; // je check si utile
	pid_t	pid[2];
}		t_pipex;

//exec folder

int		count_redir(t_ms *ms);
void	exec_command(t_ms *ms, t_pipex *px, t_token *tk);
int		exec_main(t_ms *ms);
int		exec_pipe(t_ms *ms, t_pipex *px);
void	open_and_dup(t_pipex *px, t_token *tk, t_ms *ms);
void	find_builtin(t_ms *ms, t_token *token);
void	ft_execlp(t_ms *ms, char **cmd);
void	init_pipe(t_pipex *px);
void	manage_heredoc(t_ms *ms);

//utils folder
int		count_redir_nils(t_ms *ms); // utils

//ft_cd
int		ft_cd(t_ms *ms, t_token *tk);

//ft_echo
int		ft_echo(t_ms *ms, t_token *tk);

//ft_env
int		ft_env(t_ms *ms);

//ft_exit
int		ft_exit(t_ms *ms, t_token *tk);

//ft_export
int		ft_export(t_ms *ms, t_token *token);
int		is_valid_key(char *key);
t_list	*sort_list(t_list *l, t_list *s, int (*c)(const char *, const char *));
t_list	*ft_lstdup(t_list *lst);
void	ft_putstr_export(char *key, char *value);

//ft_pwd
int		ft_pwd(t_ms *ms);

//ft_unset
int		ft_unset(t_ms *ms, t_token *token);

#endif
