/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:59 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/02 12:12:34 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Mettre mes defines
//typedef struct

# ifndef EXECUTION_H
#define EXECUTION_H

#include "../inc/minishell.h"

typedef struct s_ms_list
{
	int		status_code;
	char	*content;
	char	*token;
	int		critical;
	int		builtin;
}

#endif

