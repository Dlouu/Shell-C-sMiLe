/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_recombiner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:48:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/05 17:39:32 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//if !quoted !dquoted
void	word_splitter(t_ms *ms, t_token **tk)
{
	(void)ms;
	(void)tk;
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
*/

//recoller quand y'a un ='' ou =""
//recoller quand dquote et !blank_after_quote
//dans expander, split la fonction en 3 :
//faire une fonction pour gerer les $
//une pour les =
//une pour les dquotes!blank
