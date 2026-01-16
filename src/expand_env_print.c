/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:17:54 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/08 21:45:17 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_print(t_env *env)
{
	t_token	*current_token;

	while (env)
	{
		if (env->name)
			ft_printf("Name: [%s] Token-Count: [%i]\n",
				env->name, env->word_count);
		current_token = env->tokens;
		if (current_token)
			ft_printf("Tokens:");
		while (current_token)
		{
			ft_printf(" [%s]", current_token->value);
			current_token = current_token->next;
			if (!current_token)
				ft_printf("\n\n");
		}
		env = env->next;
	}
}
