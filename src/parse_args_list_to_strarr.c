/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_list_to_strarr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:34:18 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/07 15:18:13 by sgavrilo         ###   ########.fr       */
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

static int	merged_token_len(t_token *arg_tokens)
{
	int	merged_token_len;

	merged_token_len = 0;
	while (arg_tokens)
	{
		if (arg_tokens->value)
			merged_token_len += ft_strlen(arg_tokens->value);
		if (arg_tokens->merge == FALSE)
			break ;
		arg_tokens = arg_tokens->next;
	}
	return (merged_token_len);
}

static char	*merge_tokens_to_str(t_token *arg_tokens)
{
	int		token_len;
	char	*str;
	int		i;

	str = ft_calloc(merged_token_len(arg_tokens) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (arg_tokens)
	{
		if (arg_tokens->value)
		{
			token_len = ft_strlen(arg_tokens->value);
			ft_memcpy(&str[i], arg_tokens->value, token_len);
			if (arg_tokens->merge == FALSE)
				break ;
			i += token_len;
		}
		arg_tokens = arg_tokens->next;
	}
	return (str);
}

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

char	**args_list_to_strarr(t_arg *args_list)
{
	int		strarr_len;
	char	**strarr;

	if (!args_list)
		return (NULL);
	strarr_len = get_args_list_len(args_list);
	strarr = ft_calloc(strarr_len + 1, sizeof(char *));
	if (!strarr)
		return (NULL);
	if (put_tokens_into_strarr(args_list, &strarr) == FAILURE)
		return (NULL);
	return (strarr);
}
