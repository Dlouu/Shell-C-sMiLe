/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:13:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/25 00:43:01 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "typedefs.h"
# include "defines.h"

//env
int		find_index(char *str, char c);
t_list	*get_envp(t_ms *ms, char **envp);
t_list	*find_env_node(t_list *env, char *key);
char	*find_env_value(t_list *env, char *key);
void	del_env_node(t_list **env, char *key);
void	add_env_node(t_ms *ms, char *key_and_value);
int		env_node_exist(t_list *env, char *key);


//token lst_utils
t_token	*tk_lstnew(char *content);
void	tk_lstadd(t_token **tk_lst, t_token *new);
void	tk_lstclear(t_token **tk_lst);
void	tk_lstprint(t_ms *ms, t_token **tk_lst);

int		lexer(t_ms *ms, char *prompt);
void	tokenizer(t_ms *ms, t_token *lexed_token);

#endif