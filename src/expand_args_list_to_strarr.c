/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_list_to_strarr.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:11:46 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/11 20:20:42 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	connect_expand_tokens(t_arg *args_list)
{
	t_arg	*curr_arg;
	t_token	*curr_token;
	t_token	*curr_ex_token;

	curr_arg = args_list;
	while (curr_arg && curr_arg->arg_tokens)
	{
		curr_token = args_list->arg_tokens;
		curr_arg->expand_arg_tokens = curr_token->expand_tokens;
		while (curr_token && curr_token->expand_tokens)
		{
			curr_ex_token = curr_token->expand_tokens;
			while (curr_ex_token && curr_ex_token->next)
				curr_ex_token = curr_ex_token->next;
			curr_ex_token->next = curr_token->next->expand_tokens;
			if (curr_token->merge == FALSE)
				break ;
			curr_token = curr_token->next;
		}
		curr_arg = curr_arg->next;
	}
}

int	expand_args_list_to_strarr(t_arg *args_list, char ***strarr)
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
	if (put_expand_tokens_into_strarr(args_list, strarr) == FAILURE)
		return (free_strarr(*strarr), *strarr = 0, FAILURE);
	return (SUCCESS);
}
*/
