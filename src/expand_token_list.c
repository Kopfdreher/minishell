/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 21:49:29 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/14 21:46:02 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	copy_token_list(t_token *variable_tokens, t_token **copy_head)
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

int	expand_token_list(t_shell *shell)
{
	t_token	*current_token;

	current_token = shell->tokens;
	while (current_token)
	{
		if (expand_token(shell, &current_token) == FAILURE)
			return (FAILURE);
		current_token = current_token->next;
	}
	return (SUCCESS);
}
