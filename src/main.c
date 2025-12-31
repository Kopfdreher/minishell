/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:37:43 by sgavrilo          #+#    #+#             */
/*   Updated: 2025/12/30 20:44:06 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	shell.env_list = init_env(envp);
	while (shell.running)
	{
		shell.input = readline("minishell$ ");
		if (!shell.input)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (shell.input[0] != '\0')
			add_history(shell.input);
		// future steps
		// tokenize(&shell);
		// parse_cmds(&shell);
		// execute_cmds(&shell);
		// cleanup_cycle(&shell);
		free(shell.input);
	}
	free_env_list(&shell.env_list);
	close(shell.original_stdin);
	close(shell.original_stdout);
	return (shell.exit_status);
}
