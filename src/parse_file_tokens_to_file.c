/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_tokens_to_file.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:34:06 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/14 18:10:49 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	merge_tokens_to_error_file(t_redir *redir)
{
	t_token	*file_tokens;
	char	*new_value;
	int		new_len;

	file_tokens = redir->file_tokens;
	while (file_tokens)
	{
		if (file_tokens->quote != NO_QUOTE)
		{
			new_len = ft_strlen(file_tokens->value) + 2;
			new_value = ft_calloc(new_len + 1, sizeof(char));
			if (!new_value)
				return (FAILURE);
			new_value[0] = " '\""[file_tokens->quote];
			new_value[new_len - 1] = " '\""[file_tokens->quote];
			ft_memcpy(&new_value[1], file_tokens->value, new_len - 2);
			free(file_tokens->value);
			file_tokens->value = new_value;
		}
		file_tokens = file_tokens->next;
	}
	redir->file = merge_tokens_to_str(redir->file_tokens);
	if (!redir->file)
		return (FAILURE);
	return (SUCCESS);
}

static void	connect_expand_tokens(t_redir *redir)
{
	t_redir *curr_redir;
	t_token	*curr_token;
	t_token	*sub_list;

	curr_redir = redir;
	while (curr_redir)
	{
		curr_token = curr_redir->file_tokens;
		while (curr_token)
		{
			sub_list = curr_token->expand_tokens;
			if (sub_list)
				add_token_to_back(&curr_redir->expand_redir_tokens, sub_list);
			curr_token->expand_tokens = NULL;
			if (curr_token->merge == FALSE)
				break ;
			curr_token = curr_token->next;
		}
		curr_redir = curr_redir->next;
	}
}

static int	file_tokens_ambiguous(t_redir *redir)
{
	int		word_count;
	t_token	*current_token;

	word_count = 0;
	current_token = redir->expand_redir_tokens;
	while (current_token)
	{
		word_count++;
		while (current_token->next && current_token->merge == TRUE)
			current_token = current_token->next;
		current_token = current_token->next;
	}
	if (word_count != 1)
		redir->is_ambiguous = TRUE;
	else
		redir->is_ambiguous = FALSE;
	return (redir->is_ambiguous);
}

int	parse_file_tokens_to_file(t_redir *redir)
{
	if (!redir)
		return (SUCCESS);
	connect_expand_tokens(redir);
	if (redir->type == HEREDOC)
	{
		redir->file = merge_tokens_to_str(redir->file_tokens);
		if (!redir->file)
			return (FAILURE);
	}
	else
	{
		if (file_tokens_ambiguous(redir) == TRUE)
		{
			if (merge_tokens_to_error_file(redir) == FAILURE)
			return (FAILURE);
		}
		else
		{
			redir->file = merge_tokens_to_str(redir->expand_redir_tokens);
			if (!redir->file)
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
