/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:28:20 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/03 21:32:36 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_unexpected_token(t_token *token)
{
	if (!token)
		return ("`newline'\n");
	else if (token->type == PIPE)
		return ("`|'\n");
	else if (token->type == REDIR_IN)
		return ("`<'\n");
	else if (token->type == REDIR_OUT)
		return ("`>'\n");
	else if (token->type == APPEND)
		return ("`>>'\n");
	else if (token->type == HEREDOC)
		return ("`<<'\n");
	else
		return (NULL);
}

static int	report_syntax_error(t_shell *shell, t_token *token)
{
	put_error(SYNTAX, get_unexpected_token(token), shell);
	return (FAILURE);
}

static int	is_redir(t_token_type type)
{
	return (type >= REDIR_IN && type <= HEREDOC);
}

int	check_syntax(t_shell *shell)
{
	t_token	*current;

	if (!shell->tokens)
		return (SUCCESS);
	current = shell->tokens;
	if (current->type == PIPE)
		return (report_syntax_error(shell, current));
	while (current)
	{
		if (is_redir(current->type) == TRUE
			&& (!current->next || current->next->type != WORD))
			return (report_syntax_error(shell, current->next));
		if (current->type == PIPE
			&& (!current->next || current->next->type == PIPE))
			return (report_syntax_error(shell, current->next));
		current = current->next;
	}
	return (SUCCESS);
}
