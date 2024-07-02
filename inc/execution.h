/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:59 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/02 13:35:43 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Mettre mes defines
//typedef struct

# ifndef EXECUTION_H
#define EXECUTION_H

#include "../inc/minishell.h"

typedef struct s_ms_list //nom temporaire de test
{
	char	*content; //cmd etc.
	int		token; // (des entiers)
	int		builtin; // 0 ou 1 (Si 1, alors cest un builtin sinon cmd de base)
	int		index;
} 			t_ms;

#endif
