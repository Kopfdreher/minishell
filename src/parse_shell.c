/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:27:17 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 20:02:46 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_cmd_to_back(t_cmd *new_cmd, t_shell *shell)
{
	t_cmd	*last_cmd;

	if (shell->cmd_list == NULL)
		shell->cmd_list = new_cmd;
	else
	{
		last_cmd = shell->cmd_list;
		while (last_cmd->next != NULL)
			last_cmd = last_cmd->next;
		last_cmd->next = new_cmd;
		new_cmd->prev = last_cmd;
	}
}

static int	create_cmd(t_shell *shell, t_token **current_token)
{
	t_cmd	*new_cmd;
	int		rtrn;

	new_cmd = init_new_cmd(shell);
	if (new_cmd == NULL)
		return (FAILURE);
	rtrn = SUCCESS;
	while (*current_token && (*current_token)->type != PIPE
		&& rtrn == SUCCESS)
		rtrn = add_tokens_to_cmd(&new_cmd, current_token);
	if (rtrn == FAILURE)
		return (free_cmds(&new_cmd), FAILURE);
	if (args_list_to_strarr(new_cmd->args_list, &new_cmd->args) == FAILURE)
		return (free_cmds(&new_cmd), FAILURE);
	if (parse_file_tokens_to_file(new_cmd->redir_list) == FAILURE)
		return (free_cmds(&new_cmd), FAILURE);
	add_cmd_to_back(new_cmd, shell);
	return (SUCCESS);
}

int	parse(t_shell *shell)
{
	t_token	*current_token;

	current_token = shell->tokens;
	while (current_token)
	{
		if (create_cmd(shell, &current_token) == FAILURE)
			return (FAILURE);
		if (current_token && current_token->type == PIPE)
			current_token = current_token->next;
	}
	if (shell->cmd_list)
		print_cmds(shell->cmd_list);
	return (SUCCESS);
}
