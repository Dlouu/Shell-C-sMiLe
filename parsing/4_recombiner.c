/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_recombiner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:48:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/08 16:53:56 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	split_nodes(t_token *tk, int *i)
{
	t_token	*new;
	char	*left;
	char	*right;
	size_t	len;

	len = ft_strlen(tk->content) - *i;
	while (tk->content[*i] && !ft_isblank(tk->content[*i]))
		*i += 1;
	left = ft_substr(tk->content, 0, *i, FALSE);
	right = ft_substr(tk->content, *i + 1, len - 1, FALSE);
	tk->content = left;
	new = tk_lstnew(right);
	new->squote = tk->squote;
	new->dquote = tk->dquote;
	new->blank_before_quote = tk->blank_before_quote;
	new->blank_after_quote = tk->blank_after_quote;
	tk_lstadd_here(&tk, tk, new);
	*i = 0;
}

void	word_splitter(t_token **token)
{
	t_token	**tk;
	int		i;

	tk = token;
	while (*tk)
	{
		if ((*tk)->squote == 0 && (*tk)->dquote == 0)
		{
			i = 0;
			while ((*tk)->content[i])
			{
				if (ft_isblank((*tk)->content[i]))
					split_nodes(*tk, &i);
				i++;
			}
		}
		tk = &(*tk)->next;
	}
}

void	recombine_prev_token(t_token *tk)
{
	t_token	*prev;
	char	*new_content;

	prev = tk->prev;
	new_content = ft_strjoin(prev->content, tk->content, FALSE);
	prev->content = new_content;
	prev->type = tk->type;
	prev->next = tk->next;
	if (tk->next)
		tk->next->prev = prev;
}

void	recombine_next_token(t_token *tk)
{
	t_token	*next;
	char	*new_content;

	next = tk->next;
	new_content = ft_strjoin(tk->content, next->content, FALSE);
	tk->content = new_content;
	tk->next = next->next;
	if (next->next)
		next->next->prev = tk;
}

void	recombiner(t_token *tk)
{
	while (tk)
	{
		if (tk->prev && (tk->squote || tk->dquote) && \
			tk->blank_before_quote == 0)
			recombine_prev_token(tk);
		if (tk->next && (tk->squote || tk->dquote) && \
			tk->blank_after_quote == 0)
			recombine_next_token(tk);
		tk = tk->next;
	}
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
