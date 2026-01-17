/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:01:11 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 21:47:16 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	shell->env_list = init_env(envp);
	if (!shell->env_list)
		return (put_error(MALLOC, "minishell: Malloc failed!", shell));
	shell->env_array = NULL;
	if (execute_env_list_to_strarr(shell) == FAILURE)
		return (put_error(MALLOC, "minishell: Malloc failed!", shell));
	shell->running = TRUE;
}
