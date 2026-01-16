/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:17:49 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/16 20:58:12 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_child(pid_t pid)
{
	int	status;
	int	ret;

	ret = 0;
	if (waitpid(pid, &status, 0) == ERROR)
		return (perror("waitpid"), 1);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = WTERMSIG(status) + 128;
	return (ret);
}

int	wait_for_children(t_shell *shell)
{
	t_cmd	*cmd;
	int		ret;

	cmd = shell->cmd_list;
	ret = 0;
	while (cmd)
	{
		if (cmd->pid != ERROR)
			ret = wait_child(cmd->pid);
		cmd = cmd->next;
	}
	return (ret);
}

static void	exec_child(t_shell *shell, t_cmd *cmd)
{
	int		ret;
	char	*errorstr;

	if (is_builtin(cmd) == TRUE)
	{
		exec_builtin(cmd, shell);
		exit (0);
	}
	if (cmd->args)
	{
		ret = find_path(cmd, shell->env_list);
		if (ret == FAILURE)
		{
			errorstr = ft_strjoin(cmd->args[0], ": command not found\n");
			put_error(PATH, errorstr, shell);
			free (errorstr);
			exit (127);
		}
		else if (ret == ERROR)
		{
			put_error(MALLOC, "minishell:", shell);
			exit(1);
		}
		execve(cmd->path, cmd->args, shell->env_array);
		put_error(EXECVE, cmd->path, shell);
		exit (126);
	}
	exit (0);
}

int	execute(t_shell *shell)
{
	t_cmd	*cmd;
	int		fd[2];
	int		prev_fd;

	cmd = shell->cmd_list;
	prev_fd = -1;
	while (cmd)
	{
		if (prev_fd == -1 && !cmd->next && is_builtin(cmd))
			return (exec_builtin(cmd, shell));
		if (cmd->next)
		{
			if (pipe(fd) == ERROR)
			{
				wait_for_children(shell);
				return (put_error(PIPES, "minishell: pipe", shell), 1);
			}
		}
		cmd->pid = fork();
		if (cmd->pid == ERROR)
		{
			wait_for_children(shell);
			return (put_error(FORK, "minishell: fork", shell), 1);
		}
		if (cmd->pid == 0)
		{
			if (cmd->prev)
			{
				if (dup2(prev_fd, 0) == ERROR)
				{
					put_error(DUP2, "minishell: dup2", shell);
					exit(1);
				}
				close(prev_fd);
			}
			if (cmd->next)
			{
				if (dup2(fd[1], 1) == ERROR)
				{
					close(fd[0]);
					close(fd[1]);
					put_error(DUP2, "minishell: dup2", shell);
					exit(1);
				}
				close(fd[0]);
				close(fd[1]);
			}
			if (redirs(cmd->redir_list, shell) == FAILURE)
			{
				shell->exit_status = 1;
				exit(1);
			}
			exec_child(shell, cmd);
		}
		else 
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
			else
				prev_fd = -1;
		}
		cmd = cmd->next;
	}
	return (wait_for_children(shell));
}
