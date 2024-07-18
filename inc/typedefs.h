/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:15:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/18 14:53:59 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

//0 COMMAND			1 BUILTIN		2 ARG
//3 REDIR_LEFT		4 REDIR_RIGHT
//5 REDIR_D_LEFT 	6 REDIR_DOUBLE_RIGHT
//7 PIPE 			8 FILENAME

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
}	t_token_code;

typedef struct s_token //nom temporaire de test
{
	char			*content; //cmd etc.
	int				type; // (des entiers) COMMAND, BUILTIN, ARG, ...
	int				index; // echo -n -nnn. echo = 0, -n = 1, -nnn = 2
	int				builtin; // 1 si builtin, 0 sinon
	int				blank_after_quote;
	int				squote;
	int				dquote;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key; //PATH
	char			*value; // /usr/bin:/bin:/usr/sbin:/sbin
}	t_env;

typedef struct s_ms
{
	t_list			*env;
	struct s_token	*token;
	struct s_token	*token_lexed;
	int				blank_after_quote;
	int				exit_code;
}	t_ms;

#endif
