/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:11:21 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/09 11:09:03 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_var_name(char *key, t_token *tk, int *i)
{
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - *i - ft_strlen(key) - 1;
	left = ft_substr(tk->content, 0, *i, FALSE);
	right = ft_substr(tk->content, *i + ft_strlen(key) + 1, len, FALSE);
	tk->content = ft_strjoin(left, right, FALSE);
	*i -= 1;
}

char	*get_var(char *var)
{
	int		i;
	char	*key;

	i = 1;
	while (*var && var[i] && ft_isalnum(var[i]) && var[i] != '$'
		&& var[i] != '=' && !ft_issplitable(var[i]))
		i++;
	key = ft_substr(var, 1, i - 1, FALSE);
	return (key);
}
