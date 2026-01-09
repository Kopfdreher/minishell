/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:22:33 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/09 21:33:23 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == '\t');
}

t_token	*new_token(char	*value, t_token_type type, t_quote_type quote)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->quote = quote;
	return (new_node);
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		if (current->expand_tokens)
			free_tokens(&current->expand_tokens);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

void	add_token_back(t_token **head, t_token **tail, t_token *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		new_node->prev = *tail;
		*tail = new_node;
	}
}

void	add_token_to_back(t_token **head, t_token *new_node)
{
	t_token	*tail;

	if (!new_node)
		return ;
	if (!*head)
		*head = new_node;
	else
	{
		tail = *head;
		while (tail->next)
			tail = tail->next;
		tail->next = new_node;
	}
}
