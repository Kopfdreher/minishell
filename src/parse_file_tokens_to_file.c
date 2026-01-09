/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_tokens_to_file.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:34:06 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/09 15:55:02 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "minishell.h"

typedef struct s_redir {
	t_token_type	type;
	char			*file;
	t_token			*file_tokens;
	int				heredoc_fd;
	int				is_ambiguous;
	struct s_redir	*next;
}	t_redir;

static int	get_token_word_count(t_token *token)
{
	//int	word_count;
	//
	//word_count = 0;
	//if (token->value[0] != '$')
	//	word_count++;
	//if variable_in_token(current_token) == TRUE
	//if variable_token_count > 1
	//return (word_count)
}

static int	file_tokens_ambiguous(t_redir **redir)
{
	int	tokens_are_one_word;

	tokens_are_one_word = FALSE;
	redir->is_ambiguous = TRUE;
	current_token = redir->file_tokens;
	while (current_token)
	{
		token_word_count = get_token_word_count(current_token);
		if (token_word_count > 1)
		{
			redir->is_ambiguous == TRUE;
			return (TRUE);
		}
		if (redir->is_ambiguous == TRUE && token_word_count == 1)
			redir->is_ambiguous = FALSE;
		current_token = current_token->next;
	}
	return (redir->is_ambiguous);
}

int	parse_file_tokens_to_file(t_redir **redir)
{
	if (type == HEREDOC)
		redir->file = merge_tokens_to_str_added_quotes(redir->file_tokens);
	else
	{
		if (file_tokens_ambiguous(redir) == TRUE)
			redir->file = merge_tokens_to_error_file(redir->file_tokens);
		else if (expand_variable_tokens(redir->file_tokens) == FAILURE)
			return (FAILURE);
		else
			redir->file = merge_tokens_to_str(redir->file_tokens);
	}
	if (!redir->file)
		return (FAILURE);
	return (SUCCESS);
}
*/
