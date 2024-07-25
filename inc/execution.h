/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:59 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/25 05:30:07 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

//exec_cmd.c
void	find_builtin(t_ms *ms, t_token **token, char **envp);

//builtin
int		ft_cd(t_ms *ms);
int		ft_echo(t_ms *ms);
int		ft_env(t_ms *ms);
int		ft_exit(t_ms *ms);
int		ft_export(t_ms *ms);
int		ft_pwd(t_ms *ms);
int		ft_unset(t_ms *ms);

#endif
