/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_set_env_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 22:02:39 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 16:47:54 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_token_len(char *input)
{
	int	len;

	len = 0;
	while (input[len] && input[len] != ' ')
		len++;
	return (len);
}

int	add_env_token(char *env_value, t_token **env_tokens, int *start)
{
	t_token	*word_token;
	t_token	*last_token;
	int		len;

	word_token = new_token(NULL, WORD, NO_QUOTE);
	if (!word_token)
		return (FAILURE);
	len = get_env_token_len(&env_value[*start]);
	word_token->value = ft_substr(env_value, *start, len);
	if (!word_token->value)
		return (free_tokens(&word_token), FAILURE);
	if (*env_tokens == NULL)
		*env_tokens = word_token;
	else
	{
		last_token = *env_tokens;
		while (last_token->next != NULL)
			last_token = last_token ->next;
		last_token->next = word_token;
	}
	*start += len;
	return (SUCCESS);
}

// *env must have "NAME=VALUE"-format
int	set_env_node(t_env **env_list, char *env)
{
	char	*variable_name;
	t_env	*curr;

	if (get_variable_name(env, &variable_name) == FAILURE)
		return (FAILURE);
	curr = get_env_node(*env_list, variable_name);
	if (curr && set_new_value(curr, env) == FAILURE)
		return (free(variable_name), FAILURE);
	if (!curr && add_new_variable(env_list, env) == FAILURE)
		return (free(variable_name), FAILURE);
	free(variable_name);
	return (SUCCESS);
}
