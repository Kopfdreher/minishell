/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 15:45:47 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/10 22:27:23 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_token_type(t_token_type type)
{
	if (type == WORD)
		return ("- WORD     ");
	else if (type == PIPE)
		return ("- PIPE     ");
	else if (type == REDIR_IN)
		return ("- REDIR_IN ");
	else if (type == REDIR_OUT)
		return ("- REDIR_OUT");
	else if (type == APPEND)
		return ("- APPEND   ");
	else if (type == HEREDOC)
		return ("- HEREDOC  ");
	else
		return ("- UNKNOWN  ");
}

static const char	*get_quote_type(t_quote_type quote)
{
	if (quote == NO_QUOTE)
		return ("");
	else if (quote == SINGLE_QUOTE)
		return ("'");
	else if (quote == DOUBLE_QUOTE)
		return ("\"");
	else
		return ("UNKNOWN");
}

static const char	*get_token_value(char *value)
{
	if (!value)
		return ("");
	return (value);
}

static const char	*get_token_merge(int merge)
{
	if (merge == TRUE)
		return (" - MERGE");
	return ("");
}

void	print_tokens(t_token *tokens)
{
	int	i;
	t_token *current;

	i = 0;
	ft_printf("\nshell.tokens:\n");
	while (tokens)
	{
		ft_printf("[%i]\n[%s - %s%s%s%s]\n", i,
			get_token_type(tokens->type), get_quote_type(tokens->quote),
			get_token_value(tokens->value), get_quote_type(tokens->quote),
			get_token_merge(tokens->merge));
		current = tokens->expand_tokens;
		if (current)
		{
			ft_printf("[tokens.expanded:");
			while (current)
			{
				ft_printf(" [%s", current->value);
				if (current->merge)
					ft_printf(" Merge", current->value);
				ft_printf("]", current->value);
				current = current->next;
			}
			ft_printf("]\n");
		}
		tokens = tokens->next;
		i++;
	}
}
