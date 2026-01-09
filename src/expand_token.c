/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:24:33 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/09 21:37:40 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
t_token	*new_token(char	*value, t_token_type type, t_quote_type quote)
void	add_token_back(t_token **head, t_token **tail, t_token *new_node)
char	*ft_substr(char const *s, unsigned int start, size_t len)
t_token	*get_env_tokens(t_env *env_list, char *name)
void	add_token_to_back(t_token **head, t_token *new_node)
*/

static int	copy_token(t_token *token, t_token **copy)
{
	*copy = ft_calloc(1, sizeof(t_token));
	if (!*copy)
		return (FAILURE);
	ft_memcpy(*copy, token, sizeof(t_token));
	if (token->value)
	{
		(*copy)->value = ft_strdup(token->value);
		if (!(*copy)->value)
			return (free(*copy), FAILURE);
	}
	(*copy)->next = NULL;
	(*copy)->prev = NULL;
	return (SUCCESS);
}

static int	copy_token_list(t_token *variable_tokens, t_token **copy_head)
{
	t_token	*current_token;
	t_token	*copy;

	*copy_head = NULL;
	current_token = variable_tokens;
	while (current_token)
	{
		if (copy_token(current_token, &copy) == FAILURE)
			return (free_tokens(copy_head), FAILURE);
		add_token_to_back(copy_head, copy);
		current_token = current_token->next;
	}
	return (SUCCESS);
}

static int	add_variable_tokens(t_token **token, int *i, t_env *env_list,
				int exit_status)
{
	int		len;
	char	*variable_name;
	t_token	*variable_tokens;
	t_token	*copied_tokens;

	*i += 1;
	len = 0;
	if ((*token)->value[*i] == '?')
		return (add_expanded_exit_code(token, i, exit_status));
	while ((*token)->value[*i + len]
		&& is_variable_separator((*token)->value[*i + len]) == FALSE)
		len++;
	variable_name = ft_substr((*token)->value, *i, len);
	if (!variable_name)
		return (FAILURE);
	variable_tokens = get_env_tokens(env_list, variable_name);
	free(variable_name);
	if (copy_token_list(variable_tokens, &copied_tokens) == FAILURE)
		return (FAILURE);
	if (copied_tokens)
		add_token_to_back(&(*token)->expand_tokens, copied_tokens);
	*i += len;
	return (SUCCESS);
}

static int	add_sub_token(t_token **token, int *i)
{
	int		len;
	char	*sub_value;
	t_token	*sub_token;

	len = 0;
	while ((*token)->value[*i + len] && (*token)->value[*i + len] != '$')
		len++;
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

int	expand_token(t_shell *shell, t_token **token)
{
	int		i;
	t_token	*last_token;

	if (!token || !*token)
		return (SUCCESS);
	i = 0;
	while ((*token)->value[i])
	{
		if ((*token)->value[i] == '$' && (add_variable_tokens(token, &i,
			shell->env_list, shell->exit_status) == FAILURE))
				return (free_tokens(&(*token)->expand_tokens), FAILURE);
		else if (add_sub_token(token, &i) == FAILURE)
				return (free_tokens(&(*token)->expand_tokens), FAILURE);
	}
	last_token = (*token)->expand_tokens;
	if (last_token)
	{
		while (last_token->next)
			last_token = last_token->next;
		if (last_token->merge == TRUE)
			last_token->merge = (*token)->merge;
	}
	return (SUCCESS);
}
