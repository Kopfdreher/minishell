/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env_list_to_strarr.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 22:24:12 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 16:44:10 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_envp_len(t_env *env_list)
{
	int	len;

	len = 0;
	while (env_list)
	{
		if (env_list->value)
			len++;
		env_list = env_list->next;
	}
	return (len);
}

static int	merge_env_node_to_str(t_env *curr, char **str)
{
	int		name_len;
	int		value_len;

	name_len = ft_strlen(curr->name);
	value_len = ft_strlen(curr->value);
	*str = ft_calloc(name_len + value_len + 2, sizeof(char));
	if (!*str)
		return (FAILURE);
	ft_memcpy(*str, curr->name, name_len);
	(*str)[name_len] = '=';
	ft_memcpy(&(*str)[name_len + 1], curr->value, value_len);
	return (SUCCESS);
}

int	execute_env_list_to_strarr(t_shell *shell)
{
	int		i;
	t_env	*curr;

	shell->env_array = ft_calloc(get_envp_len(shell->env_list) + 1,
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
		if (merge_env_node_to_str(curr, &(shell->env_array)[i]) == FAILURE)
			return (free_strarr(&shell->env_array), FAILURE);
		i++;
		curr = curr->next;
	}
	return (SUCCESS);
}
