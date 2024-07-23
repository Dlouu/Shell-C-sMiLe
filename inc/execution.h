/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:59 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 08:08:47 by niabraha         ###   ########.fr       */
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

//que mettre des noms avec test a la fin pour mes structures ^.^

typedef struct s_ms_test //nom temporaire de test
{
	char				*content; //cmd etc.
	int					exit_code;
	int					type; // (des entiers)
	int					builtin; // 0 ou 1 (1 = builtin)
	int					index; // echo -n -nnn. echo = 0, -n = 1, -nnn = 2
	int					size;
	struct s_ms_test	*next;
	struct s_ms_test	*prev;
}						t_test;

typedef struct s_ms_env_test
{
	char					*key; //SHELL PATH OLDPWD
	char					*value; // /bin/bash /bin /home/niabraha
	struct s_ms_env_test	*next;
}						t_env_test;

//exec_cmd.c

void	find_builtin(t_ms *ms, t_token **token, char **envp);

//vractest.c

t_test	*create_list(int argc, char **argv);
void	is_builtin(t_ms *ms);

//cd

int		ft_cd_which_arg(t_test **lst);
int		ft_cd(t_ms *ms);
char	*find_env(char **envp, char *varenv);

//echo

int		ft_echo(t_ms *ms);

//env

int		ft_env(t_ms *ms);

//exit

int		ft_exit(t_ms *ms);

//export

int		ft_export(t_ms *ms);

// pwd

int		ft_pwd(t_ms *ms);

// unset

int		ft_unset(t_ms *ms);

//utils.c
void	free_lst(t_test **a_stack);

//test - A EFFACER
int		main_test(t_ms *ms, int argc, char **argv);

#endif
