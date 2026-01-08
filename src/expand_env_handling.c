/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:45:35 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/08 22:09:46 by sgavrilo         ###   ########.fr       */
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

static int	add_env_token(char *env_value, t_token **env_tokens, int *start)
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

static t_token	*create_env_tokens(char *env_value)
{
	int		i;
	t_token	*env_tokens;

	env_tokens = NULL;
	i = 0;
	if (!env_value)
		return (NULL);
	while (env_value[i])
	{
		if (env_value[i] == ' ')
			i++;
		else if (add_env_token(env_value, &env_tokens, &i) == FAILURE)
				return (free_tokens(&env_tokens), NULL);
	}
	return (env_tokens);
}

static int	get_word_count(char *str)
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
	}
	node->word_count = get_word_count(node->value);
	node->tokens = create_env_tokens(node->value);
	if (node->value && node->word_count && !node->tokens)
		return (free_env_list(&node), NULL);
	return (node);
}
