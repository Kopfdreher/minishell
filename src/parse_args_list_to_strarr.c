/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_list_to_strarr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:34:18 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/11 20:59:17 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
typedef struct s_token {
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	int				merge;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_arg {
	char			*arg;
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

typedef struct s_shell {
	t_cmd	*cmd_list;
	t_env	*env_list;
	t_token	*tokens;
	char	*input;
	char	**env_array;
	int		exit_status;
	int		running;
	int		original_stdin;
	int		original_stdout;
}	t_shell;
*/

static int	put_tokens_into_strarr(t_arg *args_list, char ***strarr)
{
	char	**array;
	int		i;

	array = *strarr;
	i = 0;
	while (args_list)
	{
		array[i] = merge_tokens_to_str(args_list->arg_tokens);
		if (!array[i])
			return (free_strarr(array), FAILURE);
		args_list = args_list->next;
		i++;
	}
	return (SUCCESS);
}

static int	get_args_list_len(t_arg *args_list)
{
	int		len;

	len = 0;
	while (args_list)
	{
		len++;
		args_list = args_list->next;
	}
	return (len);
}

static void	connect_expand_tokens(t_arg *args_list)
{
	t_arg	*curr_arg;
	t_token	*curr_token;
	t_token	*sub_list;
	t_token *last_node;

	curr_arg = args_list;
	while (curr_arg)
	{
		curr_token = curr_arg->arg_tokens;
		last_node = NULL;
		curr_arg->expand_arg_tokens = NULL;
		while (curr_token)
		{
			sub_list = curr_token->expand_tokens;
			if (sub_list)
			{
				if (curr_arg->expand_arg_tokens == NULL)
					curr_arg->expand_arg_tokens = sub_list;
				else
					last_node->next = sub_list;
				while (sub_list->next)
					sub_list = sub_list->next;
				last_node = sub_list;
			}
			curr_token->expand_tokens = NULL;
			if (curr_token->merge == FALSE)
				break ;
			curr_token = curr_token->next;
		}
		curr_arg = curr_arg->next;
	}
}

int	args_list_to_strarr(t_arg *args_list, char ***strarr)
{
	if (!args_list)
	{
		*strarr = NULL;
		return (SUCCESS);
	}
	connect_expand_tokens(args_list);
	*strarr = ft_calloc(get_args_list_len(args_list) + 1, sizeof(char *));
	if (!*strarr)
		return (FAILURE);
	if (put_tokens_into_strarr(args_list, strarr) == FAILURE)
		return (free_strarr(*strarr), *strarr = 0, FAILURE);
	return (SUCCESS);
}
