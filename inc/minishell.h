/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:02:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/11 10:33:02 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libft/inc/libft.h"
# include "./../libft/inc/ft_printf.h"
# include "./../libft/inc/get_next_line.h"
# include "parsing.h"
# include "execution.h"
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>

extern char	g_signal;

typedef enum e_signal
{
	READLINE,
	HEREDOC,
	FORK,
}	t_signal_type;

//0 COMMAND			1 BUILTIN		2 ARG
//3 REDIR_LEFT		4 REDIR_RIGHT
//5 REDIR_D_LEFT 	6 REDIR_DOUBLE_RIGHT
//7 PIPE 			8 FILENAME		9 DELIMITER
typedef enum e_token
{
	COMMAND,
	BUILTIN,
	ARG,
	REDIR_LEFT,
	REDIR_RIGHT,
	REDIR_DOUBLE_LEFT,
	REDIR_DOUBLE_RIGHT,
	PIPE,
	FILENAME,
	DELIMITER
}	t_token_code;

// content : echo, cmd...
// type : COMMAND, BUILTIN, ARG... enum de 0 a 9 t_token_code
// index : echo -n -nnn. echo = 0, -n = 1, -nnn = 2
// blank_info : for lexer/recombiner purpose
typedef struct s_token
{
	char			*content;
	int				type;
	int				index;
	int				blank_before;
	int				blank_after;
	int				squote;
	int				dquote;
	int				expanded;
	int				dollar;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// example :
//	*key	PATH
//	*value	/usr/bin:/bin:/usr/sbin:/sbin
typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

// prompt 		is for readline
// *token_lexed	is the first token of the linked list during parsing
// **token 		is the first token of the linked list after splitting on pipes
// blank_before	and blank_after are used to know if there is a space before
//				or after a word
// dollar		is used to know for expansion purpose
// [...]_count	is used to know how many things are in the input
// *px			is used to store the pipe structure
// [...]_path	is used to temporary store getcwd paths for the cd command
// fds_builtins	is used for the fds for the builtins
// exit_code	is used for the return value
typedef struct s_ms
{
	t_list			*env;
	char			*prompt;
	struct s_token	*token_lexed;
	struct s_token	**token;
	int				blank_before;
	int				blank_after;
	int				dollar;
	int				command_count;
	int				pipe_count;
	struct s_pipex	*px;
	char			*old_path;
	char			*new_path;
	char			*home;
	int				fds_builtins[2];
	int				i;
	int				dont_touch;
	unsigned char	exit_code;
}	t_ms;

# define MAUVE "\033[0;34m"
# define END "\033[m"

# define SQUOTE 1
# define DQUOTE 2

# define RCHEVRON 1
# define LCHEVRON 2

# define UNDERSCORE "_"

#endif
