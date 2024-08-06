/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_recombiner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:48:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/06 15:19:58 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	split_nodes(t_ms *ms, t_token **tk, int i)
// {
// }

void	word_splitter(t_ms *ms, t_token **token)
{
	t_token	**tk;
	int	i;

	(void)ms;
	tk = token;
	if ((*tk)->squote == 0 && (*tk)->dquote == 0)
	{
		i = 0;
		while ((*tk)->content[i])
		{
			if (ft_isblank((*tk)->content[i]))
				;//split_nodes(ms, tk, *i);
			i++;
		}
	}
}

void	recombiner(t_ms *ms, t_token **tk)
{
	(void)ms;
	(void)tk;
	word_splitter(ms, tk);
}

//faut que ""echo"" soit un seul token, coller et reassigner cmd
//pipe ou 0 puis mettre blank before quote

/*
else if (tk->content[i] == '\\' && tk->content[i + 1] == '$')
	i++;
else if (tk->content[i] == '=' && !tk->content[i + 1])
	printf("recombiner l'argument et continuer de check les var\n");
else if (tk->dquote == 1 && tk->blank_after_quote == 0)
	printf("recombiner l'argument et skip a la prochaine node ?\n");

bash-3.2$ "echo bite"
bash: echo bite: command not found
bash-3.2$ 'echo bite'
bash: echo bite: command not found
bash-3.2$ lololo="echo bite"
bash-3.2$ $lololo
bite
bash-3.2$ "$lololo"
bash: echo bite: command not found
bash-3.2$ '$lololo'
bash: $lololo: command not found
bash-3.2$ '$lololo lol'
bash: $lololo lol: command not found
bash-3.2$ "$lololo lol"
bash: echo bite lol: command not found

"echo bite" = ne pas split
'echo bite' = ne pas split
$lololo = split
"$lololo" = no split
'$lololo' = no split
*/

//recoller quand y'a un ='' ou =""
//recoller quand dquote et !blank_after_quote
//dans expander, split la fonction en 3 :
//faire une fonction pour gerer les $
//une pour les =
//une pour les dquotes!blank
