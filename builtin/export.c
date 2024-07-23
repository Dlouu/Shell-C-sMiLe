/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:15 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/23 06:17:15 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_export(t_ms *ms)
{
	return (ms->exit_code);
}
/* notes :
export = que pour créer
c’est unset qui delete et attention si on spécifie pas de valeur
voir avec alexis le expander “EOF” et EOF
*/

