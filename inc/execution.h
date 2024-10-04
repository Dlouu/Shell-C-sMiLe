/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:59 by niabraha          #+#    #+#             */
/*   Updated: 2024/10/04 18:06:18 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_pipex
{
	int				fd_in;
	int				fd_out;
	int				status;
	int				pipefd[2];
	int				heredoc[2];
	int				pid;
	char			*buff;
	struct s_ms		*ms;
	struct s_token	*token;
	struct s_pipex	*next;
	struct s_pipex	*prev;
}		t_pipex;

//exec folder
int		get_fds(t_ms *ms, int fd);
int		exec_main(t_ms *ms);
void	open_and_dup(t_pipex *px, t_token *tk, int is_subprocess);
void	find_builtin(t_pipex *px, t_token *token);
void	ft_execlp(t_ms *ms, char **cmd);
void	manage_heredoc(t_pipex *px, t_token *token);
char	*find_path(char *cmd, char **envp, t_ms *ms);
void	ft_close_fds(t_pipex *px);
void	ft_close_fds_builtins(t_ms *ms);
void	ft_close_pipe(int *pipe);
void	exec_sub_processus(t_pipex *px, int i);
void	manage_execve(t_pipex *px, char **cmd, char **envp);
void	ft_perror(char *error, int critical);
void	ft_error(char *error, char *details, int critical, int exit_code);
t_pipex	*setup_pipe(t_ms *ms);

//ft_cd
int		ft_cd(t_ms *ms, t_token *tk);

//ft_echo
int		ft_echo(t_ms *ms, t_token *tk);

//ft_env
int		ft_env(t_ms *ms);

//ft_exit
int		ft_exit(t_ms *ms, t_token *tk);
void	clean_exit(int exit_code, char *error);

//ft_export
int		ft_export(t_ms *ms, t_token *token);
int		is_valid_key(char *key);
t_list	*sort_list(t_list *l, t_list *s, int (*c)(const char *, const char *));
t_list	*ft_lstdup(t_list *lst);
void	ft_putstr_export(t_ms *ms, char *key, char *value);

//ft_pwd
int		ft_pwd(t_ms *ms);

//ft_unset
int		ft_unset(t_ms *ms, t_token *token);

#endif
