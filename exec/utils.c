/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:29:45 by niabraha          #+#    #+#             */
/*   Updated: 2024/09/19 16:41:33 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	ft_perror(char *error, int critical)
{
	perror(error);
	if (critical == 1)
		exit(errno);
}

void	ft_error(char *error, char *details, int critical, int exit_code)
{
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, details, ft_strlen(details));
	write(2, "\n", 1);
	if (critical == 1)
		exit(exit_code);
}

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
