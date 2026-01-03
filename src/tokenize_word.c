/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 19:09:53 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/03 20:52:06 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '<'
		|| c == '>' || c == '\'' || c == '"')
		return (TRUE);
	return (FALSE);
}

static int	is_merge(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ' ' || c == '\t'
		|| c == '\0' || c == '\n')
		return (FALSE);
	return (TRUE);
}

static char	get_quote_char(t_quote_type quote)
{
	if (quote == SINGLE_QUOTE)
		return ('\'');
	else
		return ('"');
}

static int	get_token_len(char *input, t_token *word_token)
{
	int				len;
	int				quote_char;
	t_quote_type	quote;

	len = -1;
	quote = word_token->quote;
	if (quote != NO_QUOTE)
	{
		quote_char = get_quote_char(quote);
		while (input[++len])
		{
			if (input[len] == quote_char)
			{
				if (is_merge(input[len + 1]) == TRUE)
					word_token->merge = TRUE;
				return (len);
			}
		}
		return (-1);
	}
	while (input[++len] && is_separator(input[len]) == FALSE)
		len = len + 0; // not clean, change
	if (is_merge(input[len]) == TRUE)
		word_token->merge = TRUE;
	return (len);
}

int	add_word_token(t_shell *shell, t_token **last_token, int *start)
{
	t_token	*word_token;
	int		len;

	word_token = new_token(NULL, WORD, NO_QUOTE);
	if (word_token == NULL)
		return (FAILURE);
	if (shell->input[*start] == '"')
		word_token->quote = DOUBLE_QUOTE;
	else if (shell->input[*start] == '\'')
		word_token->quote = SINGLE_QUOTE;
	if (word_token->quote != NO_QUOTE)
		*start += 1;
	len = get_token_len(&shell->input[*start], word_token);
	if (len == -1)
		return (put_error(SYNTAX, "`newline'\n", shell), FAILURE);
	word_token->value = ft_substr(shell->input, *start, len);
	if (!word_token->value)
		return (FAILURE);
	add_token_back(&shell->tokens, last_token, word_token);
	*start += len;
	if (word_token->quote != NO_QUOTE)
		*start += 1;
	return (SUCCESS);
}
