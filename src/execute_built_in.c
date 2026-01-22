/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:50:18 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 15:50:08 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	char	*command;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (FALSE);
	command = cmd->args[0];
	if ((ft_strncmp(command, "echo", 5) == 0
			|| ft_strncmp(command, "cd", 3) == 0
			|| ft_strncmp(command, "pwd", 4) == 0
			|| ft_strncmp(command, "export", 7) == 0
			|| ft_strncmp(command, "unset", 6) == 0
			|| ft_strncmp(command, "env", 4) == 0
			|| ft_strncmp(command, "exit", 5) == 0))
		return (TRUE);
	else
		return (FALSE);
}

int	handle_lonely_builtin(t_shell *shell)
{
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	if (redirs(shell->cmd_list->redir_list, shell) == FAILURE)
		shell->exit_status = 1;
	else 
		shell->exit_status = exec_builtin(shell->cmd_list, shell);
	dup2(shell->original_stdin, STDIN_FILENO);
	dup2(shell->original_stdout, STDOUT_FILENO);
	close(shell->original_stdin);
	close(shell->original_stdout);
	return (shell->exit_status);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	**commands;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (FALSE);
	commands = cmd->args;
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		return (ft_echo(commands));
	else if (ft_strncmp(commands[0], "cd", 3) == 0)
		return (ft_cd(commands, shell));
	else if (ft_strncmp(commands[0], "pwd", 4) == 0)
		return (ft_pwd(shell));
	else if (ft_strncmp(commands[0], "export", 7) == 0)
		return (ft_export(shell, commands));
	else if (ft_strncmp(commands[0], "unset", 6) == 0)
		return (ft_unset(shell, commands));
	else if (ft_strncmp(commands[0], "env", 4) == 0)
		return (ft_env(shell));
	else if (ft_strncmp(commands[0], "exit", 5) == 0)
		return (ft_exit(commands, shell));
	return (SUCCESS);
}
