/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_sign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:08:17 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/17 17:14:15 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_variable_sign(t_token **token)
{
	char	*dollar_sign;
	t_token	*variable_token;

	dollar_sign = ft_calloc(2, sizeof(char));
	if (!dollar_sign)
		return (FAILURE);
	dollar_sign[0] = '$';
	variable_token = new_token(dollar_sign, WORD, NO_QUOTE);
	if (!variable_token)
		return (free(dollar_sign), FAILURE);
	variable_token->merge = TRUE; // check if correct
	add_token_to_back(&(*token)->expand_tokens, variable_token);
	return (SUCCESS);
}
