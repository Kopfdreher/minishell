/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 21:23:45 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/09 21:39:16 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_expanded_exit_code(t_token **token, int *i, int exit_code)
{
	char	*exit_str;
	t_token	*exit_token;

	*i += 1;
	exit_str = ft_itoa(exit_code);
	if (!exit_str)
		return (FAILURE);
	exit_token = new_token(exit_str, WORD, NO_QUOTE);
	if (!exit_token)
		return (free(exit_str), FAILURE);
	add_token_to_back(&(*token)->expand_tokens, exit_token);
	return (SUCCESS);
}
