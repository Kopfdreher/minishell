/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:00:36 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/15 13:46:19 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_shell_lvl(t_env	*env_list)
{
	t_env	*lvl_node;
	char	*new_lvl;
	int		lvl_num;

	lvl_node = get_env_node(env_list, "SHLVL");
	if (!lvl_node || !lvl_node->value)
		return (SUCCESS);
	lvl_num = ft_atoi(lvl_node->value);
	lvl_num += 1;
	new_lvl = ft_itoa(lvl_num);
	if (!new_lvl)
		return (FAILURE);
	free(lvl_node->value);
	lvl_node->value = new_lvl;
	return (SUCCESS);
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
	if (set_shell_lvl(head) == FAILURE)
		return (free_env_list(&head), NULL);
	return (head);
}

void	free_env_list(t_env **env_list)
{
	t_env	*current;
	t_env	*temp;

	if (!env_list || !*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		temp = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		if (current->tokens)
			free_tokens(&current->tokens);
		free(current);
		current = temp;
	}
	*env_list = NULL;
}
