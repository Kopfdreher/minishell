/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:44:57 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 16:16:33 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_child(pid_t pid, int is_last)
{
	int	status;
	int	ret;
	int	sig;

	if (waitpid(pid, &status, 0) == ERROR)
		return (perror("waitpid"), FAILURE);
	ret = 0;
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		ret = 128 + sig;
		if (is_last)
		{
			if (sig == SIGINT)
				write(1, "\n", 1);
			else if (sig == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", 2);
		}
	}
	return (ret);
}

int	wait_for_children(t_shell *shell)
{
	t_cmd	*cmd;
	int		ret;
	int		is_last;

	cmd = shell->cmd_list;
	ret = 0;
	while (cmd)
	{
		if (cmd->next == NULL)
			is_last = TRUE;
		else
			is_last = FALSE;
		if (cmd->pid != ERROR)
			ret = wait_child(cmd->pid, is_last);
		cmd = cmd->next;
	}
	return (ret);
}
