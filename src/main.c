/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:37:43 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/03 21:50:01 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//volatile sig_atomic_t	g_signal_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	if (!shell.env_list)
		return (1);
	while (shell.running == TRUE)
	{
		shell.input = readline("minishell$ ");
		if (!shell.input || !ft_strncmp(shell.input, "exit\0", 5))
		{
			write(1, "exit\n", 5);
			shell.running = FALSE;
		}
		else if (shell.input[0] != '\0')
			add_history(shell.input);
		if (tokenize(&shell) == SUCCESS) 
		{
			// parse_cmds(&shell);
			// execute_cmds(&shell);
		}
		// if (shell.running == FALSE)
		// 	cleanup_cycle(&shell);
		free(shell.input);
		free_tokens(&shell.tokens);
	}
	rl_clear_history();
	free_env_list(&shell.env_list);
	close(shell.original_stdin);
	close(shell.original_stdout);
	return (shell.exit_status);
}
