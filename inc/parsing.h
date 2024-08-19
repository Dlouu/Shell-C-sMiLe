/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:13:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/19 15:36:39 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_token	t_token_code;
typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_ms		t_ms;

//parsing
int		lexer(t_ms *ms, char *prompt, t_token *token_lst);
int		tokenizer(t_ms *ms);
void	expander(t_ms *ms, t_token *tk, int i);
void	recombiner(t_token *tk);
void	word_splitter(t_token **token);
int		parser(t_ms *ms, char *prompt);
void	pipe_splitter(t_ms *ms);
int		count_heredoc(t_ms *ms);

//env
char	**env_lst_to_tab(t_ms *ms);
t_list	*get_envp(t_ms *ms, char **envp);
t_list	*find_env_node(t_list *env, char *key);
char	*find_env_value(t_list *env, char *key);
void	del_env_node(t_list **env, char *key);
void	add_env_node(t_ms *ms, char *key_and_value);
int		env_node_exist(t_list *env, char *key);
void	replace_env_value(t_list *env, char *key, char *value);

//token lst_utils
t_token	*tk_lstnew(char *content);
void	tk_lstadd(t_token **tk_lst, t_token *new);
void	tk_lstadd_here(t_token **lst, t_token *here, t_token *new);
void	tk_lstclear(t_token **tk_lst);
void	tk_lstprint(t_ms *ms, t_token **tk_lst);

//utils
int		error_free_prompt(t_ms *ms, char *prompt, char *error);
void	set_interactive_signals(void);
int		find_index(char *str, char c);
void	update_index(t_token **tk);
char	*get_var(char *var);
void	delete_var_name(char *key, t_token *tk, int *i);

#endif