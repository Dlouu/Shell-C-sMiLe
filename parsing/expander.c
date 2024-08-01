/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:06:12 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/01 22:19:42 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	expander(t_ms *ms)
{
	t_token	*tk;
	int		i;

	tk = ms->token_lexed;
	while (tk)
	{
		i = 0;
		while (tk->content[i])
		{
			if (tk->content[i] == '$' && tk->squote == 0)
			{
				printf("$ trouvé\n");
				//compter le nombre de $ car faut repasser plusieurs fois
				if (tk->content[i + 1] == '?')
				{
					printf("? trouvé, faut mettre le exit code ici\n");
					//wfree, puis itoa, puis ft_strjoin ?
				}
				else if (tk->dquote == 1)
				{
					printf("dquote avec $, on cherche le env mais on \
					split pas\n");
				}
				else if (!tk->content[i + 1])
				{
					printf("pas de env à chercher\n");
				}
				else
				{
					printf("pas de ? alors on cherche le env correspondant, \
					si on ne trouve pas, on delete le truc\n");
				}
			}
			i++;
		}
		tk = tk->next;
	}
}
