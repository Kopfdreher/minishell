/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:37:43 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/26 22:03:46 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

static void	cleanup_cycle(t_shell *shell)
{
	free_heredocs_lst(&shell->heredocs);
	free(shell->input);
	free_cmds(&shell->cmd_list);
	free_tokens(&shell->tokens);
	free_strarr(&shell->env_array);
}

static int	cleanup_exit(t_shell *shell)
{
	rl_clear_history();
	free_env_list(&shell->env_list);
	close(shell->original_stdin);
	close(shell->original_stdout);
	ft_putendl_fd("exit", 1);
	return (shell->exit_status);
}

static void	prompt_cycle(t_shell *shell)
{
	int		exec_status;

	if (g_signal_status != 0)
	{
		shell->exit_status = g_signal_status;
		g_signal_status = 0;
	}
	if (shell->running == FALSE)
		return ;
	if (tokenize(shell) == SUCCESS) 
	{
		if (parse(shell) == SUCCESS)
		{
			if (preprocess_heredocs(shell) == ERROR)
			{
				if (g_signal_status == 130)
					shell->exit_status = 130;
				return ;
			}
			exec_status = execute(shell);
			clean_heredocs(shell);
			if (g_signal_status == 0)
				shell->exit_status = exec_status;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (init_shell(&shell, argc, argv, envp) == FAILURE)
		return (FAILURE);
	while (shell.running == TRUE)
	{
		set_signals(SIG_INTERACTIVE);
		g_signal_status = 0;
		shell.input = readline("minishell$ ");
		if (!shell.input)
			shell.running = FALSE;
		else if (shell.input[0] != '\0')
			add_history(shell.input);
		prompt_cycle(&shell);
		cleanup_cycle(&shell);
	}
	return (cleanup_exit(&shell));
}
