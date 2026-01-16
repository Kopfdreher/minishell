/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:24:33 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 16:46:56 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_variable_tokens(t_token **token, int *i, t_env *env_list,
				int exit_status)
{
	*i += 1;
	if ((*token)->value[*i] == '?')
		return (add_expanded_exit_code(token, i, exit_status));
	else if ((*token)->quote == NO_QUOTE)
		return (add_expanded_tokens(token, i, env_list));
	else if ((*token)->quote == DOUBLE_QUOTE)
		return (add_expanded_str(token, i, env_list));
	return (SUCCESS);
}

static int	add_sub_token(t_token **token, int *i)
{
	int		len;
	char	*sub_value;
	t_token	*sub_token;

	len = 0;
	if ((*token)->quote != SINGLE_QUOTE)
	{
		while ((*token)->value[*i + len] && (*token)->value[*i + len] != '$')
			len++;
	}
	else
	{
		while ((*token)->value[*i + len])
			len++;
	}
	sub_value = ft_substr((*token)->value, *i, len);
	if (!sub_value)
		return (FAILURE);
	sub_token = new_token(sub_value, WORD, NO_QUOTE);
	if (!sub_token)
		return (free(sub_value), FAILURE);
	sub_token->merge = TRUE;
	add_token_to_back(&(*token)->expand_tokens, sub_token);
	*i += len;
	return (SUCCESS);
}

static void	inherit_parent_merge(t_token **token)
{
	t_token	*last_expand_token;

	last_expand_token = (*token)->expand_tokens;
	if (last_expand_token)
	{
		while (last_expand_token->next)
			last_expand_token = last_expand_token->next;
		if (last_expand_token->merge == TRUE)
			last_expand_token->merge = (*token)->merge;
	}
}

int	expand_token(t_shell *shell, t_token **token)
{
	int		i;

	if (!token || !*token)
		return (SUCCESS);
	i = 0;
	while ((*token)->value)
	{
		if ((*token)->value[i] == '$' && (*token)->quote != SINGLE_QUOTE)
		{
			if (add_variable_tokens(token, &i, shell->env_list,
					shell->exit_status) == FAILURE)
				return (free_tokens(&(*token)->expand_tokens), FAILURE);
		}
		else 
		{
			if (add_sub_token(token, &i) == FAILURE)
				return (free_tokens(&(*token)->expand_tokens), FAILURE);
		}
		if ((*token)->value[i] == '\0')
			break ;
	}
	inherit_parent_merge(token);
	return (SUCCESS);
}
