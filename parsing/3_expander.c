/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:06:12 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/02 11:45:57 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	expand_var_and_split(t_ms *ms, t_token *tk)
{
	(void)tk;
	(void)ms;
	printf("si var trouvé, faut mettre le env ici\n");
	printf("on resplit si nécessaire\n");
}

void	expand_var_dquoted(t_ms *ms, t_token *tk)
{
	(void)tk;
	(void)ms;
	printf("si var trouvé, faut mettre le env ici\n");
	printf("mais on resplit pas\n");
}

//fautdra break par bloc de $$
//$$$ = pid + $
//$$ = pid
//$$$$ = pid + pid
void	expand_pid_number(t_ms *ms, t_token *tk)
{
	(void)tk;
	(void)ms;
	printf("$$ trouvé, faut mettre le pid ici\n");
}

void	expand_exit_code(t_ms *ms, t_token *tk, int *i)
{
	char	*exit_code;
	char	*left;
	char	*right;
	char	*temp;
	size_t	len;

	temp = tk->content;
	len = ft_strlen(tk->content) - *i - 2;
	left = ft_substr(tk->content, 0, *i, FALSE);
	exit_code = ft_itoa(ms->exit_code, FALSE);
	right = ft_substr(tk->content, *i + 2, len, FALSE);
	tk->content = ft_free_strjoin(left, exit_code, FALSE);
	tk->content = ft_strjoin(tk->content, right, FALSE);
	wfree(temp);
	wfree(right);
	*i += ft_strlen(exit_code) - 1;
}

void	expander(t_ms *ms, t_token *tk, int i)
{
	while (tk)
	{
		i = -1;
		while (tk->content[++i])
		{
			if (tk->content[i] == '$' && tk->squote == 0)
			{
				if (tk->content[i + 1] == '?')
					expand_exit_code(ms, tk, &i);
				else if (!tk->content[i + 1])
					break ;
				else if (tk->content[i + 1] == '$')
					expand_pid_number(ms, tk);
				else if (tk->dquote == 1)
					expand_var_dquoted(ms, tk);
				else
					expand_var_and_split(ms, tk);
			}
		}
		tk = tk->next;
	}
}

/*
else if (tk->content[i] == '\\' && tk->content[i + 1] == '$')
	i++;
else if (tk->content[i] == '=' && !tk->content[i + 1])
	printf("recombiner l'argument et continuer de check les var\n");
else if (tk->dquote == 1 && tk->blank_after_quote == 0)
	printf("recombiner l'argument et skip a la prochaine node ?\n");
*/

//recoller quand y'a un ='' ou =""
//recoller quand dquote et !blank_after_quote
//dans expander, split la fonction en 3 :
//faire une fonction pour gerer les $
//une pour les =
//une pour les dquotes!blank
