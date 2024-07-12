/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:15:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/12 18:47:14 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEFS_H
# define TYPEDEFS_H

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
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key; //PATH
	char			*value; // /usr/bin:/bin:/usr/sbin:/sbin
	struct s_env	*next;
}	t_env;

typedef struct s_ms
{
	struct s_env	*env;
	struct s_token	*token;
	int				exit_code;
}	t_ms;

#endif
