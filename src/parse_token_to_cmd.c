/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_to_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:03:16 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/07 20:03:50 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_arg_to_cmd(t_cmd **cmd, t_token **current_token)
{
	t_arg	*new_arg;
	t_arg	*last_arg;

	new_arg = ft_calloc(1, sizeof(t_arg));
	if (!new_arg)
		return (FAILURE);
	new_arg->arg_tokens = *current_token;
	if ((*cmd)->args_list == NULL)
		(*cmd)->args_list = new_arg;
	else
	{
		last_arg = (*cmd)->args_list;
		while (last_arg->next != NULL)
			last_arg = last_arg->next;
		last_arg->next = new_arg;
	}
	while ((*current_token)->merge == TRUE)
		*current_token = (*current_token)->next;
	*current_token = (*current_token)->next;
	return (SUCCESS);
}

static int	add_redir_to_cmd(t_cmd **cmd, t_token **current_token)
{
	t_redir	*new_redir;
	t_redir	*last_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (FAILURE);
	new_redir->type = (*current_token)->type;
	*current_token = (*current_token)->next;
	new_redir->file_tokens = *current_token;
	if ((*cmd)->redir_list == NULL)
		(*cmd)->redir_list = new_redir;
	else
	{
		last_redir = (*cmd)->redir_list;
		while (last_redir->next != NULL)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
	if (parse_file_tokens_to_file(&new_redir) == FAILURE)
		return (FAILURE);
	while ((*current_token)->merge == TRUE)
		*current_token = (*current_token)->next;
	*current_token = (*current_token)->next;
	return (SUCCESS);
}

static int	is_redir(t_token_type type)
{
	return (type == HEREDOC || type == APPEND
		|| type == REDIR_IN || type == REDIR_OUT);
}

int	add_tokens_to_cmd(t_cmd **cmd, t_token **current_token)
{
	if (is_redir((*current_token)->type) == TRUE)
		return (add_redir_to_cmd(cmd, current_token));
	else 
	{
		return (add_arg_to_cmd(cmd, current_token));
	new_cmd->args = args_list_to_strarr(new_cmd->args_list);
}
