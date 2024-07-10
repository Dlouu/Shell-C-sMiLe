/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedefs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:15:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/10 15:21:02 by mbaumgar         ###   ########.fr       */
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
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

#endif
