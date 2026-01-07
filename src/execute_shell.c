/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:17:49 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/07 18:27:20 by alago-ga         ###   ########.fr       */
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

/*static void	exec_builtin(shell, cmd)
{
}
*/
static void	exec_child(t_shell *shell, t_cmd *cmd)
{
/*	if (cmd->is_builtin == TRUE)
	{
		exec_builtin(shell, cmd);
		exit (0);
	}*/
	cmd->path = find_path(cmd, shell);
	if (!cmd->path)
	{
		write(2, "minishelf: command not found: ", 30);
		ft_putendl_fd(cmd->args[0], 2);
		exit (127);
	}
	execve(cmd->path, cmd->args, shell->env_array);
	perror("minishell");
	//fee cmdpath?;
	exit (126);
}

static int	redirs(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redir_list;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == HEREDOC)
			fd = open_heredoc(redir);
		if (fd == ERROR)
			return (put_error(OPEN, redir->file), 1);
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			if (dup2(fd, 0) == ERROR)
			{
				put_error(DUP2, fd);
				close(fd);
				return (1);
			}
		}
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
		{
			if (dup2(fd, 1) == ERROR)
			{
				put_error(DUP2, fd);
				close(fd);
				return (1);
			}
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
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
		if (cmd->next)
		{
			if (pipe(fd) == ERROR)
			{
				wait_for_children(shell);
				return (perror("pipe"), 1);
			}
		}
		cmd->pid = fork();
		if (cmd->pid == ERROR)
		{
			wait_for_children(shell);
			return (perror("fork"), 1);
		}
		if (cmd->pid == 0)
		{
			if (cmd->prev)
			{
				if (dup2(prev_fd, 0) == ERROR)
				{
					perror("minishell");
					exit(3);
				}
				close(prev_fd);
			}
			if (cmd->next)
			{
				if (dup2(fd[1], 1) == ERROR)
				{
					perror("minishell");
					exit(3);
				}
				close(fd[0]);
				close(fd[1]);
			}
			if (redirs(cmd) == FAILURE)
				exit(1);
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
