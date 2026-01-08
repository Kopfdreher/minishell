/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_to_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:26:24 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/08 21:09:28 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	merged_token_len(t_token *tokens)
{
	int	merged_token_len;

	merged_token_len = 0;
	while (tokens)
	{
		if (tokens->value)
			merged_token_len += ft_strlen(tokens->value);
		if (tokens->merge == FALSE)
			break ;
		tokens = tokens->next;
	}
	return (merged_token_len);
}

char	*merge_tokens_to_str(t_token *tokens)
{
	int		token_len;
	char	*str;
	int		i;

	str = ft_calloc(merged_token_len(tokens) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->value)
		{
			token_len = ft_strlen(tokens->value);
			ft_memcpy(&str[i], tokens->value, token_len);
			if (tokens->merge == FALSE)
				break ;
			i += token_len;
		}
		tokens = tokens->next;
	}
	return (str);
}
