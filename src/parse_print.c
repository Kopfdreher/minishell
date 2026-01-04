/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:59:45 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/04 18:07:53 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_cmd *cmd_list)
{
	while (cmd_list)
	{
		ft_printf("CMD: %s\N", cmd_list->args_list->arg_tokens->value);
		cmd_list = cmd_list->next;
	}
}
