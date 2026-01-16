/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:58:33 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 19:47:37 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *shell)
{
	t_env	*curr;

	curr = shell->env_list;
	while (curr)
	{
		if (curr->value && curr->value[0])
			ft_printf("%s=%s\n", curr->name, curr->value);
		curr = curr->next;
	}
	return (SUCCESS);
}

int	env_parameter_shift(char ***args)
{
	char	**new_args;

	if (!*args || !(*args)[0] || ft_strncmp(**args, "env", 4) || !(*args)[1])
		return (SUCCESS);
	new_args = ft_strarrcpy(&(*args)[1]);
	if (!new_args)
		return (FAILURE);
	free_strarr(args);
	*args = new_args;
	if (env_parameter_shift(args) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
