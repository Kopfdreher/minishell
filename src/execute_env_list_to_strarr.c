/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env_list_to_strarr.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 22:24:12 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/15 18:00:57 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_list_len(t_env *env_list)
{
	int	len;

	len = 0;
	while (env_list)
	{
		len++;
		env_list = env_list->next;
	}
	return (len);
}

int	execute_env_list_to_strarr(t_shell *shell)
{
	int		i;
	int		name_len;
	int		value_len;
	t_env	*curr;

	shell->env_array = ft_calloc(get_env_list_len(shell->env_list) + 1,
			sizeof(char *));
	if (!shell->env_array)
		return (FAILURE);
	curr = shell->env_list;
	i = 0;
	while (curr)
	{
		if (!curr->value)
		{
			curr = curr->next;
			continue ;
		}
		name_len = ft_strlen(curr->name);
		value_len = ft_strlen(curr->value);
		shell->env_array[i] = ft_calloc(name_len + value_len + 2, sizeof(char));
		if (!shell->env_array[i])
			return (free_strarr(&shell->env_array), FAILURE);
		ft_memcpy(shell->env_array[i], curr->name, name_len);
		shell->env_array[i][name_len] = '=';
		ft_memcpy(&(shell->env_array[i])[name_len + 1], curr->value, value_len);
		i++;
		curr = curr->next;
	}
	return (SUCCESS);
}
