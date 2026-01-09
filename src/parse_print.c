/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:59:45 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/09 14:06:48 by sgavrilo         ###   ########.fr       */
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

typedef struct s_arg {
	t_token			*arg_tokens;
	struct s_arg	*next;
}	t_arg;

typedef struct s_redir {
	t_token_type	type;
	char			*file;
	t_token			*file_tokens;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;
*/

static void	print_args_list(t_arg *args_list)
{
	int		i;
	t_token	*current_token;

	i = 0;
	while (args_list)
	{
		current_token = args_list->arg_tokens;
		if (i == 0)
			ft_printf("CMD:");
		else if (i == 1)
			ft_printf("\nARGS:");
		ft_printf(" [");
		while (current_token)
		{
			ft_printf("%s", current_token->value);
			if (current_token->merge == FALSE)
				break ;
			current_token = current_token->next;
		}
		ft_printf("]");
		args_list = args_list->next;
		i++;
	}
	ft_printf("\n");
}

static const char	*get_redir_type(t_token_type type)
{
	if (type == REDIR_IN)
		return ("REDIR_IN");
	else if (type == REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else
		return ("UNKNOWN");
}

static void	print_redir_list(t_redir *redir_list)
{
	int		i;
	t_token	*current_token;

	i = 0;
	while (redir_list)
	{
		current_token = redir_list->file_tokens;
		if (i == 0)
			ft_printf("REDIRECTIONS:");
		ft_printf(" [%s:", get_redir_type(redir_list->type));
		while (current_token)
		{
			ft_printf("%s", current_token->value);
			if (current_token->merge == FALSE)
				break ;
			current_token = current_token->next;
		}
		ft_printf("]");
		redir_list = redir_list->next;
		i++;
	}
	ft_printf("\n");
}

void	print_cmds(t_cmd *cmd_list)
{
	int		i;
	t_cmd	*current_cmd;
	t_env	*env_node;

	i = 0;
	current_cmd = cmd_list;
	ft_printf("\nshell.cmd_list:\n");
	while (current_cmd)
	{
		ft_printf("- CMD %i --------------------------------------------\n", i);
		if (current_cmd->args_list)
			print_args_list(current_cmd->args_list);
		if (current_cmd->redir_list)
			print_redir_list(current_cmd->redir_list);
		ft_printf("\ncmd_list.args: (converted to strarr)\n");
		print_strarr(current_cmd->args);
		i++;
		ft_printf("env.path.value:\n%s\n", get_env_value(
			current_cmd->shell->env_list, "X"));
		env_node = get_env_node(current_cmd->shell->env_list, "X");
		if (env_node)
			ft_printf("env.path.node.value:\n%s\n", env_node->value);
		ft_printf("----------------------------------------------------\n\n");
		current_cmd = current_cmd->next;
	}
}
