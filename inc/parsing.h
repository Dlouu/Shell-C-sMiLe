/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:13:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/09/11 14:12:02 by mbaumgar         ###   ########.fr       */
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
void	word_splitter(t_ms *ms, int i);
int		parser(t_ms *ms, char *prompt);
void	pipe_splitter(t_ms *ms);
void	sort_token(t_ms *ms);

//env
t_list	*get_envp(t_ms *ms, char **envp);
t_list	*find_env_node(t_list *env, char *key);
char	*find_env_value(t_list *env, char *key);
void	add_env_node(t_ms *ms, char *key_and_value);
void	del_env_node(t_list **env, char *key);
char	*get_var(char *var);
int		env_node_exist(t_list *env, char *key);
void	delete_var_name(char *key, t_token *tk, int *i);
void	replace_env_value(t_list *env, char *key, char *value);
char	**env_lst_to_tab(t_ms *ms);

//token lst_utils
t_token	*tk_lstnew(char *content);
t_token	*tk_delone(t_token **tk_lst, t_token *tk);
t_token	*tk_lstfirst(t_token *tk);
t_token	*tk_lstlast(t_token *tk);
void	tk_lstadd(t_token **tk_lst, t_token *new);
void	tk_lstadd_here(t_token *here, t_token *new);
void	tk_lstclear(t_token **tk_lst);
void	tk_lstprint(t_ms *ms, t_token **tk_lst);
void	tk_lstprint_type(t_token *tk);
void	move_token_to_front(t_token **to_move);

//error
int		error_free_prompt(t_ms *ms, char *prompt, char *error);
int		empty_prompt(char *prompt);

//utils
void	set_readline_signals(void);
int		find_index(char *str, char c);
void	update_index(t_ms *ms);
char	**cmd_to_tab(t_ms *ms, t_token *tk);
void	go_to_next_quote(char *prompt, int *i, int *quote, int type);

#endif
