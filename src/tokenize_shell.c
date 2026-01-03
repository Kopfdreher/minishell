/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:16:32 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/03 20:12:30 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_operator_token(t_shell *shell, t_token **last_token, int *i,
				t_token_type type)
{
	t_token	*operator_token;

	operator_token = new_token(NULL, type, NO_QUOTE);
	if (!operator_token)
		return (FAILURE);
	add_token_back(&shell->tokens, last_token, operator_token);
	if (type == HEREDOC || type == APPEND)
		*i += 2;
	else
		*i += 1;
	return (SUCCESS);
}

static int	create_token(t_shell *shell, t_token **last_token, int *i)
{
	if (shell->input[*i] == '<' && shell->input[*i + 1] == '<')
		return (add_operator_token(shell, last_token, i, HEREDOC));
	else if (shell->input[*i] == '>' && shell->input[*i + 1] == '>')
		return (add_operator_token(shell, last_token, i, APPEND));
	else if (shell->input[*i] == '<')
		return (add_operator_token(shell, last_token, i, REDIR_IN));
	else if (shell->input[*i] == '>')
		return (add_operator_token(shell, last_token, i, REDIR_OUT));
	else if (shell->input[*i] == '|')
		return (add_operator_token(shell, last_token, i, PIPE));
	else
		return (add_word_token(shell, last_token, i));
}

void	tokenize(t_shell *shell)
{
	int		i;
	t_token	*last_token;

	last_token = NULL;
	if (shell->running == FALSE)
		return ;
	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == ' ') // change ' ' to is_whitespace()
			i++;
		else
		{
			if (create_token(shell, &last_token, &i) == FAILURE)
			{
				free_tokens(&shell->tokens);
				break ;
			}
		}
	}
	print_tokens(shell->tokens);
}
