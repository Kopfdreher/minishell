/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:31:37 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/08 18:58:27 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args_list(t_arg **args_list)
{
	t_arg	*current;
	t_arg	*next;

	if (!args_list || !*args_list)
		return ;
	current = *args_list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	args_list = NULL;
}

static void	free_redir_list(t_redir **redir_list)
{
	t_redir	*current;
	t_redir	*next;

	if (!redir_list || !*redir_list)
		return ;
	current = *redir_list;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
	redir_list = NULL;
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmds || !*cmds)
		return ;
	current = *cmds;
	while (current)
	{
		next = current->next;
		if (current->args)
			free_strarr(current->args);
		if (current->path)
			free(current->path);
		if (current->args_list)
			free_args_list(&current->args_list);
		if (current->redir_list)
			free_redir_list(&current->redir_list);
		free(current);
		current = next;
	}
	*cmds = NULL;
}

t_cmd	*init_new_cmd(t_shell *shell)
{
	t_cmd	*new_node;

	new_node = ft_calloc(1, sizeof(t_cmd));
	if (new_node == NULL)
		return (NULL);
	new_node->fd_out = STDOUT_FILENO;
	new_node->pid = -1;
	new_node->shell = shell;
	return (new_node);
}
