/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:47:50 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/16 22:59:04 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc(int fd, int expand, char *eof, t_shell *shell)
{
	char	*line;
	char	*error_string;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			error_string = ft_strjoin(eof, "')\n");
			put_error(H_DOC, error_string, shell);
			free(error_string);
			return (0);
		}
		if (ft_strncmp(line, eof, (ft_strlen(eof) + 1)) == SUCCESS)
		{
			free(line);
			return (0);
		}
		if (expand == TRUE)
			line = NULL;
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static int	open_heredoc(t_redir *heredoc, t_shell *shell)
{
	int		fd;
	char	*eof;
	int		expand;

	eof = heredoc->file_tokens->value;
	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	expand = FALSE;
	read_heredoc(fd, expand, eof, shell);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	unlink("/tmp/.heredoc");
	return (fd);
}

static int	open_redirs(int *fd, t_redir *redir, t_shell *shell)
{
	if (redir->type == REDIR_IN)
		*fd = open(redir->file_tokens->value, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		*fd = open(redir->file_tokens->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		*fd = open(redir->file_tokens->value, 
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == HEREDOC)
		*fd = open_heredoc(redir, shell);
	if (*fd == ERROR)
		return (put_error(OPEN, redir->file_tokens->value, shell), 1);
	return (0);
}

int	redirs(t_redir *redir, t_shell *shell)
{
	int		fd;

	fd = -1;
	while (redir)
	{
		if (open_redirs(&fd, redir, shell) == FAILURE)
			return (FAILURE);
		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			if (dup2(fd, 0) == ERROR)
			{
				put_error(DUP2, "", shell);
				close(fd);
				return (1);
			}
		}
		else if (redir->type == REDIR_OUT || redir->type == APPEND)
		{
			if (dup2(fd, 1) == ERROR)
			{
				put_error(DUP2, "", shell);
				close(fd);
				return (1);
			}
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}
