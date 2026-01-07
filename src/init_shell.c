/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:01:11 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/07 17:24:57 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->running = TRUE;
	shell->exit_status = 0;
	shell->tokens = NULL;
	shell->env_array = envp;
	shell->cmd_list = NULL;
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	shell->env_list = init_env(envp);
}
