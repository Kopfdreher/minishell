/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:50:18 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/14 17:54:07 by alago-ga         ###   ########.fr       */
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

int	exec_builtin(t_cmd *cmd)
{
	(void)cmd;

	return (SUCCESS);
}
