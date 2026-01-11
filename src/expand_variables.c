/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 21:23:45 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/11 17:43:56 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_expanded_exit_code(t_token **token, int *i, int exit_code)
{
	char	*exit_str;
	t_token	*exit_token;

	*i += 1;
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		return (FAILURE);
	exit_token = new_token(exit_str, WORD, NO_QUOTE);
	if (!exit_token)
		return (free(exit_str), FAILURE);
	exit_token->merge = TRUE;
	add_token_to_back(&(*token)->expand_tokens, exit_token);
	return (SUCCESS);
}

static void	pre_merge_correction(t_token **token, t_token *expand_tokens)
{
	t_token	*current;
	if (expand_tokens->prev == NULL && (*token)->prev != NULL)
	{
		//(*token)->prev->merge = FALSE;
		current = (*token)->prev->expand_tokens;
		if (current)
		{
			while (current->next)
				current = current->next;
			current->merge = FALSE;
		}
	}
	else if (expand_tokens->prev != NULL)
		expand_tokens->prev->merge = FALSE;
}

int	add_expanded_tokens(t_token **token, int *i, t_env *env_list)
{
	int		len;
	char	*variable_name;
	t_env	*variable_node;
	t_token	*copied_tokens;

	len = 0;
	while ((*token)->value[*i + len]
		&& is_variable_separator((*token)->value[*i + len]) == FALSE)
		len++;
	if (len == 0)
		return (SUCCESS);
	variable_name = ft_substr((*token)->value, *i, len);
	if (!variable_name)
		return (FAILURE);
	variable_node = get_env_node(env_list, variable_name);
	free(variable_name);
	if (variable_node == NULL)
		return (*i += len, SUCCESS);
	if (copy_token_list(variable_node->tokens, &copied_tokens) == FAILURE)
		return (FAILURE);
	add_token_to_back(&(*token)->expand_tokens, copied_tokens);
	if (variable_node->value[0] == ' ')
		pre_merge_correction(token, copied_tokens);
	return (*i += len, SUCCESS);
}

int	add_expanded_str(t_token **token, int *i, t_env *env_list)
{
	int		len;
	char	*variable_name;
	char	*variable_value;
	char	*copied_value;
	t_token	*copied_token;

	len = 0;
	while ((*token)->value[*i + len]
		&& is_variable_separator((*token)->value[*i + len]) == FALSE)
		len++;
	if (len == 0)
		return (SUCCESS);
	variable_name = ft_substr((*token)->value, *i, len);
	if (!variable_name)
		return (FAILURE);
	variable_value = get_env_value(env_list, variable_name);
	free(variable_name);
	if (variable_value == NULL)
		return (*i += len, SUCCESS);
	copied_value = ft_strdup(variable_value);
	if (!copied_value)
		return (FAILURE);
	if (*copied_value == '\0')
		return (free(copied_value), copied_value = NULL, SUCCESS);
	copied_token = new_token(copied_value, WORD, NO_QUOTE);
	if (!copied_token)
		return (free(copied_value), FAILURE);
	copied_token->merge = TRUE;
	add_token_to_back(&(*token)->expand_tokens, copied_token);
	return (*i += len, SUCCESS);
}
