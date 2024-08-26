/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:29:45 by niabraha          #+#    #+#             */
/*   Updated: 2024/08/26 15:22:53 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int	count_redir_nils(t_ms *ms)
{
	t_token	**tk_lst;
	t_token	*tk;
	int		i;
	int		count_redir;

	tk_lst = ms->token;
	i = 0;
	count_redir = 0;
	while (tk_lst[i])
	{
		tk = tk_lst[i];
		while (tk->next)
		{
			if (tk->type == REDIR_LEFT || tk->type == REDIR_DOUBLE_LEFT || tk->type == REDIR_RIGHT || tk->type == REDIR_DOUBLE_RIGHT)
				count_redir++;
			tk = tk->next;
		}
		i++;
	}
	return (count_redir);
}
