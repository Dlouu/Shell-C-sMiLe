/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:13:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/05 20:58:13 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_token	t_token_code;
typedef enum e_signal	t_signal_type;
typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_ms		t_ms;

//parsing
int		lexer(t_ms *ms, char *prompt, t_token *token_lst);
int		tokenizer(t_ms *ms);
void	expander(t_ms *ms, t_token *tk, int i);
void	recombiner(t_token *tk);
void	word_splitter(t_ms *ms, int i);
int		parser(t_ms *ms);
void	pipe_splitter(t_ms *ms);
void	sort_token(t_ms *ms);

//expander
int		expand_empty_quote(t_token *tk, int *i);
void	expand_var(t_ms *ms, t_token *tk, int *i);
void	expand_pid_number(t_token *tk, int *i);
void	expand_exit_code(t_ms *ms, t_token *tk, int *i);

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

//error
int		error_parsing(t_ms *ms, char *error);
int		empty_prompt(char *prompt);

//utils
void	set_signals(t_signal_type mode);
int		find_index(char *str, char c);
void	update_index(t_ms *ms);
char	**cmd_to_tab(t_ms *ms, t_token *tk);
int		check_quotes(t_ms *ms, char *prompt, int *i);
int		check_unclosed_quote(char *prompt);

#endif
