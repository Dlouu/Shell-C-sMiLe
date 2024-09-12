/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:02:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/09/12 14:45:37 by niabraha         ###   ########.fr       */
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

extern int	g_signal;

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

//content : echo, cmd...
//type : COMMAND, BUILTIN, ARG... enum de 0 a 11 t_token_code
//index : echo -n -nnn. echo = 0, -n = 1, -nnn = 2
//builtin : 1 si builtin, 0 sinon
typedef struct s_token
{
	char			*content;
	int				type;
	int				index;
	int				blank_before_quote;
	int				blank_after_quote;
	int				squote;
	int				dquote;
	int				expanded;
	int				dollar;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//	*key	PATH
//	*value	/usr/bin:/bin:/usr/sbin:/sbin
typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef struct s_ms
{
	t_list			*env;
	char			*path;
	struct s_token	**token;
	struct s_token	*token_lexed;
	struct s_pipex	*px;
	int				blank_before_quote;
	int				blank_after_quote;
	int				dollar;
	int				current_pipe;
	int				pipe_count;
	int				heredoc_count;
	int				heredoc_count_check;
	int				command_count;
	unsigned char	exit_code;
}	t_ms;

# define MAUVE "\033[0;34m"
# define END "\033[m"

# define SIG_REST_SIGINFO 0
# define SIG_DEFAULT 1
# define SIG_IGNORE 2
# define SIG_INTERACTIVE 3

# define SQUOTE 1
# define DQUOTE 2

# define RCHEVRON 1
# define LCHEVRON 2

# define UNDERSCORE "_"

#endif
