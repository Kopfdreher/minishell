/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:47:50 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/12 17:28:00 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(t_redir *heredoc, t_shell *shell)
{
	char	*line;
	int		fd;
	char	*eof;

	eof = heredoc->file_tokens->value;
	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			eof = ft_strjoin(eof, "')\n");
			put_error(H_DOC, eof, shell);
			free(eof);
			break ;
		}
		if (ft_strncmp(line, eof, (ft_strlen(eof) + 1)) == SUCCESS)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	unlink("/tmp/.heredoc");
	return (fd);
}

int	redirs(t_redir *redir, t_shell *shell)
{
	int		fd;

	fd = -1;
	while (redir)
	{
		if (redir->type == REDIR_IN)
			fd = open(redir->file_tokens->value, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->file_tokens->value,
			 \O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->file_tokens->value, 
			 \O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == HEREDOC)
			fd = open_heredoc(redir, shell);
		if (fd == ERROR)
			return (put_error(OPEN, redir->file_tokens->value, shell), 1);
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
