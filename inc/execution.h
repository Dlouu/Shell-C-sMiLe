/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:59 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/03 17:42:16 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Mettre mes defines
//typedef struct

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../inc/minishell.h"
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

typedef struct s_ms_list //nom temporaire de test
{
	char				*content; //cmd etc.
	int					exit_code;
	int					token; // (des entiers)
	int					builtin; // 0 ou 1 (1 = builtin)
	int					index; // echo -n -nnn. echo = 0, -n = 1, -nnn = 2
	int					size;
	struct s_ms_list	*next;
	struct s_ms_list	*prev;
}						t_ms;

//exec_cmd.c

void	find_builtin(t_ms **test, char **envp);

//vractest.c

t_ms	*create_list(int argc, char **argv);
void	is_builtin(t_ms **test);

//cd

int		ft_cd_which_arg(t_ms **lst);
int		ft_cd(t_ms **lst);
char	*find_path(char **envp, char *varenv);
char	*find_env(char **envp, char *varenv);

//echo

int		ft_echo(t_ms **lst);

// env

int		ft_env(t_ms **lst, char **envp);

// pwd

int		ft_pwd(t_ms **lst);

//utils.c
void	free_lst(t_ms **a_stack);
void	error_message(const char *message, int status_code);

#endif
