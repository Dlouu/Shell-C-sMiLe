/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:02:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/25 05:28:24 by mbaumgar         ###   ########.fr       */
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
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

//0 COMMAND			1 BUILTIN		2 ARG
//3 REDIR_LEFT		4 REDIR_RIGHT
//5 REDIR_D_LEFT 	6 REDIR_DOUBLE_RIGHT
//7 PIPE 			8 FILENAME		9 VAR
//10 VAR_ENV		11 VAR_EXPORT
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
	VAR,
	VAR_ENV,
	VAR_EXPORT
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
	int				builtin;
	int				blank_after_quote;
	int				squote;
	int				dquote;
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
	int				blank_after_quote;
	int				pipe_count;
	int				exit_code;
}	t_ms;

# define MAUVE "\033[0;34m"
# define END "\033[m"

# define SQUOTE 1
# define DQUOTE 2

# define RCHEVRON 1
# define LCHEVRON 2

# define ERR_QUOTE 1

# define UNDERSCORE "_"

#endif
