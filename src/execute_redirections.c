/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:47:50 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/21 19:39:13 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_redirs(int *fd, t_redir *redir, t_shell *shell)
{
	if (redir->type == REDIR_IN)
		*fd = open(redir->file, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		*fd = open(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		*fd = open(redir->file, 
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == HEREDOC)
	{
		*fd = open_heredoc(redir, shell);
		return (*fd);
	}
	if (*fd == ERROR)
		return (put_error(OPEN, redir->file, shell), 1);
	return (0);
}

static int	dup_redir(int fd, int direction, t_shell *shell)
{
	if (dup2(fd, direction) == ERROR)
	{
		put_error(DUP2, "", shell);
		close (fd);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	redirs(t_redir *redir, t_shell *shell)
{
	int		fd;

	while (redir)
	{
		fd = -1;
		if (open_redirs(&fd, redir, shell) == FAILURE)
			return (FAILURE);
		if (fd != ERROR)
		{
			if (redir->type == REDIR_IN || redir->type == HEREDOC)
			{
				if (dup_redir(fd, 0, shell) == FAILURE)
					return (FAILURE);
			}
			else if (redir->type == REDIR_OUT || redir->type == APPEND)
			{
				if (dup_redir(fd, 1, shell) == FAILURE)
					return (FAILURE);
			}
			close(fd);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}
