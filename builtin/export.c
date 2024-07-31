/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:49:15 by niabraha          #+#    #+#             */
/*   Updated: 2024/07/25 16:11:55 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Faire un sas pour traiter differemment les VAR, VAR_ENV et VAR_EXPORT
//si VAR_ENV on met juste le nom de la var
//si VAR_EXPORT on met le nom de la var et la valeur
//si y'a un egal il faut mettre ="" sinon juste le nom de la var (key)
//export caca != export caca="" != caca=""

//sur mac : export caca    ->   caca=''       wtf

//path si on en trouve pas au lancement, faut qu'on en assign un genre de base

//si y'a un egal il faut mettre ="" sinon juste le nom de la var (key)
//export nom sans egal = liste de VAR (s'affiche dans export mais pas dans env)
//meme comportement pour zzz=zzzz sans export devant

//export CACA
//si exist osef
//si exist pas on cree sans le =

void	update_or_create_var(t_ms *ms, t_token **token)
{
	t_list	*env;
	t_list	*env_to_update;
	size_t	equals;
	size_t	len;
	char	*extracted_key;

	env = ms->env;
	len = ft_strlen((*token)->content);
	equals = find_index((*token)->content, '=');
	extracted_key = ft_substr((*token)->content, 0, equals, FALSE);
	if (find_env_node(env, extracted_key) != NULL)
	{
		env_to_update = find_env_node(env, extracted_key);
		if (((t_env *)env_to_update->data)->value)
			wfree(((t_env *)env_to_update->data)->value);
		((t_env *)env_to_update->data)->value = ft_substr((*token)->content, \
		equals + 1, len, TRUE);
	}
	else
		add_env_node(ms, (*token)->content);
}

int	*ft_add_var(t_ms *ms)
{
	t_token	**token;

	token = ms->token;
	*token = (*ms->token)->next;
	while (token && *token)
	{
		if (is_valid_key((*token)->content))
			update_or_create_var(ms, token);
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd((*token)->content, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ms->exit_code = 1;
		}
		*token = (*token)->next;
	}
	return (&ms->exit_code);
}

int	ft_export(t_ms *ms)
{
	t_list	*unsorted_env;
	t_list	*sorted_env;
	t_token	**token;

	unsorted_env = ft_lstdup(ms->env);
	sorted_env = sort_list(unsorted_env, NULL, ft_strcmp);
	token = ms->token;
	if (!(*token)->next)
	{
		while (sorted_env)
		{
			if (!ft_strcmp(((t_env *)sorted_env->data)->key, UNDERSCORE))
			{
				sorted_env = sorted_env->next;
				continue ;
			}
			ft_putstr_export(((t_env *)sorted_env->data)->key, \
			(((t_env *)sorted_env->data)->value));
			sorted_env = sorted_env->next;
		}
	}
	else
		ft_add_var(ms);
	return (ms->exit_code);
}
