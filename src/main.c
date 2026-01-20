/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:37:43 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/20 18:49:46 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		execute_status;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	if (!shell.env_list)
		return (1);
	while (shell.running == TRUE)
	{
		set_signals(SIG_INTERACTIVE);
		g_signal_status = 0;
//		if (isatty(STDIN_FILENO) == TRUE)
		shell.input = readline("minishell$ ");
	//	else
	//		shell.input = get_next_line(STDIN_FILENO);
		if (g_signal_status != 0)
		{
			shell.exit_status = g_signal_status;
			g_signal_status = 0;
		}
		if (!shell.input)
			shell.running = FALSE;
		else if (shell.input[0] != '\0')
			add_history(shell.input);
		if (tokenize(&shell) == SUCCESS) 
		{
			if (parse(&shell) == SUCCESS)
			{
				execute_status = execute(&shell);
				if (g_signal_status == 0)
					shell.exit_status = execute_status;
			}
			// if (shell.running == TRUE && tokenize)
			// 		if (shell.running == TRUE && parse)
			// 			if (shell.running == TRUE && execute)
		}
		// if (shell.running == FALSE)
		// 	cleanup_cycle(&shell);
		free(shell.input);
		free_cmds(&shell.cmd_list);
		free_tokens(&shell.tokens);
		free_strarr(&shell.env_array);
	}
	rl_clear_history();
	free_env_list(&shell.env_list);
	close(shell.original_stdin);
	close(shell.original_stdout);
	return (shell.exit_status);
}
