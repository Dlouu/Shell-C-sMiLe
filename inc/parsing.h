/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:13:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/01 16:14:58 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "typedefs.h"
# include "defines.h"

int     find_index(char *str, char c);
t_list  *get_envp(t_ms *ms, char **envp);
t_list  *find_env_node(t_list *env, char *key);
char    *find_env_value(t_list *env, char *key);

#endif