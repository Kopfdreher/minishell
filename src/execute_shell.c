/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:17:49 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 22:39:28 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_shell *shell, t_cmd *cmd)
{
	int		ret;

	if (is_builtin(cmd) == TRUE)
		exit(exec_builtin(cmd, shell));
	if (cmd->args && cmd->args[0])
	{
		ret = find_path(cmd, shell->env_list);
		if (ret != SUCCESS)
			exit(handle_path_ret(ret, shell, cmd));
		if (execute_env_list_to_strarr(shell) == FAILURE)
		{
			put_error(MALLOC, "minishell:", shell);
			exit(1);
		}
		execve(cmd->path, cmd->args, shell->env_array);
		ft_putstr_fd(cmd->path, 2);
		put_error(EXECVE, ": Is a directory\n", shell);
		exit (126);
	}
	exit(0);
}

static void	prep_write_fd(int fd[], t_shell *shell)
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

static void	handle_child(t_shell *shell, t_cmd *cmd, int prev_fd, int fd[])
{
	set_signals(SIG_EXEC_CHILD);
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
		prep_write_fd(fd, shell);
	if (redirs(cmd->redir_list, shell) == FAILURE)
	{
		if (g_signal_status == 130)
			exit(130);
		exit(1);
	}
	exec_child(shell, cmd);
}

static void	parental_control(int *prev_fd, int fd[], t_cmd *cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
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
			return (handle_lonely_builtin(shell));
		if (cmd->next && pipe(fd) == ERROR)
			return (put_error(PIPES, "pipe", shell), wait_for_children(shell));
		cmd->pid = fork();
		if (cmd->pid == ERROR)
			return (put_error(FORK, "fork", shell), wait_for_children(shell));
		if (cmd->pid == 0)
			handle_child(shell, cmd, prev_fd, fd);
		else 
			parental_control(&prev_fd, fd, cmd);
		cmd = cmd->next;
	}
	set_signals(SIG_EXEC_PARENT);
	shell->exit_status = wait_for_children(shell);
	set_signals(SIG_INTERACTIVE);
	return (shell->exit_status);
}
