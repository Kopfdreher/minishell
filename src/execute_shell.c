/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:17:49 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 18:07:23 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_shell *shell, t_cmd *cmd)
{
	int		ret;
	char	*errorstr;

	if (is_builtin(cmd) == TRUE)
		exit (exec_builtin(cmd, shell));
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
		errorstr = ft_strjoin(cmd->path, ": Is a directory\n");
		if (!errorstr)
		{
			put_error(MALLOC, "minishell:", shell);
			exit(1);
		}
		put_error(EXECVE, errorstr, shell);
		free(errorstr);
		exit (126);
	}
	exit (0);
}

static int	handle_lonely_builtin(t_shell *shell)
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
		if (g_signal_status == 130)
			exit (130);
		exit(1);
	}
	exec_child(shell, cmd);
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
			handle_child(shell, cmd, prev_fd, fd);
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
	set_signals(SIG_EXEC_PARENT);
	shell->exit_status = wait_for_children(shell);
	set_signals(SIG_INTERACTIVE);
	return (shell->exit_status);
}
