/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_env_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:20:13 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 21:01:06 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// we have to add one to compare_len for the /0-Terminator
t_env	*get_env_node(t_env *env_list, char *name)
{
	t_env	*current_node;
	int		compare_len;

	if (!name)
		return (NULL);
	compare_len = ft_strlen(name) + 1;
	current_node = env_list;
	while (current_node)
	{
		if (ft_strncmp(current_node->name, name, compare_len) == SUCCESS)
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env_list, char *name)
{
	t_env	*env_node;

	env_node = get_env_node(env_list, name);
	if (env_node == NULL)
		return (NULL);
	return (env_node->value);
}

t_token	*get_env_tokens(t_env *env_list, char *name)
{
	t_env	*env_node;

	env_node = get_env_node(env_list, name);
	if (env_node == NULL)
		return (NULL);
	return (env_node->tokens);
}

int	is_variable_separator(char c)
{
	return (ft_isalnum(c) == FALSE && c != '_');
}
