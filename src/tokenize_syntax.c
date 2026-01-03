/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:28:20 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/03 17:04:58 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_unexpected_token(t_token *token)
{
	if (!token)
		return ("`newline'\n");
	if (token->type == PIPE)
		return ("`|'\n");
	if (token->type == REDIR_IN)
		return ("`<'\n");
	if (token->type == REDIR_OUT)
		return ("`>'\n");
	if (token->type == APPEND)
		return ("`>>'\n");
	if (token->type == HEREDOC)
		return ("`<<'\n");
	return (NULL);
}

static int	report_syntax_error(t_shell *shell, t_token *token)
{
	put_error(SYNTAX, get_unexpected_token(token), shell);
	return (FAILURE);
}

int	check_syntax(t_shell *shell, t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (SUCCESS);
	current = tokens;
	if (current->type == PIPE)
		return (report_syntax_error(shell, current));
	while (current)
	{
		if (current->type >= REDIR_IN && current->type <= HEREDOC)
		{
			if (!current->next || current->next->type != WORD)
				return (report_syntax_error(shell, current->next));
		}
		if (current->type == PIPE)
		{
			if (!current->next)
				return (report_syntax_error(shell, NULL));
			if (current->next->type == PIPE)
				return (report_syntax_error(shell, current->next));
		}
		current = current->next;
	}
	return (SUCCESS);
}
