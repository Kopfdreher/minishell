/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:10:24 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/26 20:40:37 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_heredocs(t_shell *shell)
{
	t_list	*current;
	t_redir	*redir;

	current = shell->heredocs;
	while (current)
	{
		redir = (t_redir *)current->content;
		if (redir->file)
		{
			unlink(redir->file);
			free(redir->file);
			redir->file = NULL;
		}
		current = current->next;
	}
}

static char	*get_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*filename;

	num = ft_itoa(i++);
	filename = ft_strjoin("/tmp/.heredoc", num);
	free(num);
	return (filename);
}

static int	create_file(t_redir *redir, t_shell *shell, char *filename)
{
	int		fd;
	int		expand;
	char	*eof_str;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == ERROR)
		return (free(filename), put_error(OPEN, "heredoc", shell), ERROR);
	expand = expand_heredoc(redir->file_tokens);
	eof_str = merge_tokens_to_str(redir->file_tokens);
	if (!eof_str)
		return (close(fd), put_error(MALLOC, "heredoc", shell), ERROR);
	set_signals(SIG_HEREDOC);
	if (read_heredoc(fd, expand, eof_str, shell) == FAILURE)
	{
		set_signals(SIG_INTERACTIVE);
		free(eof_str);
		close(fd);
		return (ERROR);
	}
	set_signals(SIG_INTERACTIVE);
	close(fd);
	free(eof_str);
	return (SUCCESS);
}

int	preprocess_heredocs(t_shell *shell)
{
	t_list	*current;
	t_redir	*redir;
	char	*filename;

	current = shell->heredocs;
	while (current)
	{
		redir = (t_redir *)current->content;
		filename = get_heredoc_filename();
		if (!filename)
			return (put_error(MALLOC, "heredoc", shell), ERROR);
		if (create_file(redir, shell, filename) == ERROR)
			return (free(filename), ERROR);
		free(redir->file);
		redir->file = filename;
		redir->type = REDIR_IN;
		current = current->next;
	}
	return (SUCCESS);
}
