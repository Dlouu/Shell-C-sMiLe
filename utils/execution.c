/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:50:11 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/02 13:42:11 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
# include <stdio.h> // a enlever
// mon main de test

int main()
{
	t_ms bite;

	bite.content = "ls";
	bite.token = 2;
	printf("%d\n", bite.token);
	printf("%s\n", bite.content);
}