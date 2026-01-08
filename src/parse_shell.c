/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:27:17 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/08 21:14:14 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
typedef struct s_cmd {
	char			**args;
	char			*path;
	int				is_builtin;
	t_arg			*args_list;
	t_redir			*redir_list;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
}	t_cmd;

typedef struct s_token {
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	int				merge;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_arg {
	t_token			*arg_tokens;
	struct s_arg	*next;
}	t_arg;

typedef struct s_redir {
	t_token_type	type;
	t_token			*file_tokens;
	char			*file;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

int	open_redir(t_redir *
*/

static int	create_cmd(t_shell *shell, t_token **current_token)
{
	t_cmd	*new_cmd;
	t_cmd	*last_cmd;
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
	// new_cmd->args should be somewhere else, here just for testing
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
	return (rtrn);
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
