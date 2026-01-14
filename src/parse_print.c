/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:59:45 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/14 17:47:38 by sgavrilo         ###   ########.fr       */
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

static void	print_args_list(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (i == 0)
			ft_printf("CMD:");
		else if (i == 1)
			ft_printf("\nARGS:");
		ft_printf(" [%s]", args[i]);
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

	i = 0;
	while (redir_list)
	{
		if (i == 0)
			ft_printf("REDIRECTIONS:");
		ft_printf(" [%s: [%s]", get_redir_type(redir_list->type),
			redir_list->file);
		if (redir_list->is_ambiguous == TRUE)
			ft_printf(" is Ambiguous");
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

	i = 0;
	current_cmd = cmd_list;
	ft_printf("\nshell.cmd_list:\n");
	while (current_cmd)
	{
		ft_printf("- CMD %i --------------------------------------------\n", i);
		if (current_cmd->args)
			print_args_list(current_cmd->args);
		if (current_cmd->redir_list)
			print_redir_list(current_cmd->redir_list);
		i++;
		ft_printf("----------------------------------------------------\n\n");
		current_cmd = current_cmd->next;
	}
}
