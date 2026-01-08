/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_tokens_to_file.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 18:34:06 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/08 15:33:39 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
typedef struct s_redir {
	t_token_type	type;
	char			*file;
	t_token			*file_tokens;
	int				heredoc_fd;
	int				is_ambiguous;
	struct s_redir	*next;
}	t_redir;
*/
static int	file_tokens_ambiguous(t_redir **redir)
{
	redir->is_ambiguous = TRUE;
}

int	parse_file_tokens_to_file(t_redir **redir)
{
	if (type == HEREDOC)
		redir->file = merge_tokens_to_str(redir->file_tokens);
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
