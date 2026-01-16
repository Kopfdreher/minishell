/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:58:36 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 19:50:30 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *shell, char **args)
{
	int		i;
	t_env	*curr;

	i = 0;
	while (args[++i])
	{
		curr = get_env_node(shell->env_list, args[i]);
		if (curr)
		{
			if (curr->prev)
				curr->prev->next = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			free_env_list(&curr);
		}
	}
	return (SUCCESS);
}
