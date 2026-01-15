/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:45:35 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/15 20:37:55 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*merge_correction(t_token *env_tokens, int trailing_space)
{
	t_token	*last_token;

	if (!env_tokens)
		return (env_tokens);
	last_token = env_tokens;
	while (last_token->next)
		last_token = last_token->next;
	if (trailing_space == FALSE)
		last_token->merge = TRUE;
	return (env_tokens);
}

t_token	*create_env_tokens(char *env_value)
{
	int		i;
	int		trailing_space;
	t_token	*env_tokens;

	env_tokens = NULL;
	i = 0;
	trailing_space = FALSE;
	if (!env_value)
		return (NULL);
	while (env_value[i])
	{
		if (env_value[i] == ' ')
		{
			trailing_space = TRUE;
			i++;
		}
		else
		{
			trailing_space = FALSE;
			if (add_env_token(env_value, &env_tokens, &i) == FAILURE)
				return (free_tokens(&env_tokens), NULL);
		}
	}
	return (merge_correction(env_tokens, trailing_space));
}

int	get_word_count(char *str)
{
	int	i;
	int	word_count;
	int	in_word;

	in_word = FALSE;
	word_count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && in_word == FALSE)
		{
			in_word = TRUE;
			word_count++;
		}
		else if (str[i] == ' ')
			in_word = FALSE;
	}
	return (word_count);
}

t_env	*new_env_node(char *str)
{
	t_env	*node;
	int		i;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	node->name = ft_substr(str, 0, i);
	if (!node->name)
		return (free(node), NULL);
	if (str[i])
	{
		node->value = ft_strdup(str + i + 1);
		if (!node->value)
			return (free_env_list(&node), NULL);
		node->word_count = get_word_count(node->value);
		node->tokens = create_env_tokens(node->value);
		if (node->value && node->word_count && !node->tokens)
			return (free_env_list(&node), NULL);
	}
	return (node);
}
