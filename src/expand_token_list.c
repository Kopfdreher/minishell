/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 21:49:29 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/10 22:40:28 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_token_list(t_shell *shell)
{
	t_token	*current_token;

	current_token = shell->tokens;
	while (current_token)
	{
		if (current_token->quote != SINGLE_QUOTE
			&& expand_token(shell, &current_token) == FAILURE)
			return (FAILURE);
		current_token = current_token->next;
	}
	return (SUCCESS);
}
