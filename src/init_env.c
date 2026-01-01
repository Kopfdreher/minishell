/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:00:36 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/01 22:17:24 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_env *new_env_node(char *str)
{
	t_env	*node;
	int		i;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	node->name = ft_substr(str, 0, i);
	if (str[i])
		node->value = ft_strdup(str + i + 1);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = -1;
	while (envp[++i])
	{
		new_node = new_env_node(envp[i]);
		if (head && !new_node)
			return (free_env_list(&head), NULL);
		if (!head && !new_node)
			return (NULL);
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
	}
	return (head);
}

void	free_env_list(t_env **env_list)
{
	t_env	*current;
	t_env	*temp;

	if(!env_list || !*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		temp = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
	*env_list = NULL;
}
