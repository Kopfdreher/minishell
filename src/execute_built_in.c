/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:50:18 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/16 16:50:34 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	char	*command;

	if (!cmd || !cmd->args)
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

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	**commands;

	if (!cmd || !cmd->args)
		return (FALSE);
	commands = cmd->args;
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		ft_echo(commands);
	else if (ft_strncmp(commands[0], "cd", 3) == 0)
		ft_cd(commands, shell);
	else if (ft_strncmp(commands[0], "pwd", 4) == 0)
		ft_pwd(shell);
	return (SUCCESS);
}
