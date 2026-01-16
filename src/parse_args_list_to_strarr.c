/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_list_to_strarr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:34:18 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 21:02:21 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	put_tokens_into_strarr(t_cmd *cmd, char ***strarr)
{
	char	**array;
	t_token	*current;
	int		i;

	array = *strarr;
	current = cmd->expand_arg_tokens;
	i = 0;
	while (current)
	{
		array[i] = merge_tokens_to_str(current);
		if (!array[i])
			return (FAILURE);
		while (current->merge == TRUE && current->next)
			current = current->next;
		current = current->next;
		i++;
	}
	return (SUCCESS);
}

static int	get_args_list_len(t_cmd *cmd)
{
	int		len;
	t_token	*current;

	len = 0;
	current = cmd->expand_arg_tokens;
	while (current)
	{
		if (current->merge == FALSE)
			len++;
		current = current->next;
	}
	return (len);
}

static void	connect_expand_arg_tokens(t_cmd *cmd)
{
	t_arg	*curr_arg;
	t_token	*sub_list;

	curr_arg = cmd->args_list;
	while (curr_arg)
	{
		sub_list = curr_arg->expand_arg_tokens;
		if (sub_list)
			add_token_to_back(&cmd->expand_arg_tokens, sub_list);
		curr_arg->expand_arg_tokens = NULL;
		curr_arg = curr_arg->next;
	}
}

static void	connect_expand_tokens(t_arg *args_list)
{
	t_arg	*curr_arg;
	t_token	*curr_token;
	t_token	*sub_list;

	curr_arg = args_list;
	while (curr_arg)
	{
		curr_token = curr_arg->arg_tokens;
		while (curr_token)
		{
			sub_list = curr_token->expand_tokens;
			if (sub_list)
				add_token_to_back(&curr_arg->expand_arg_tokens, sub_list);
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
	connect_expand_arg_tokens(args_list->cmd);
	*strarr = ft_calloc(get_args_list_len(args_list->cmd) + 1, sizeof(char *));
	if (!*strarr)
		return (FAILURE);
	if (put_tokens_into_strarr(args_list->cmd, strarr) == FAILURE)
		return (free_strarr(strarr), *strarr = NULL, FAILURE);
	if (env_parameter_shift(strarr) == FAILURE)
		return (free_strarr(strarr), *strarr = NULL, FAILURE);
	return (SUCCESS);
}
