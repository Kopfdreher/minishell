/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:23:14 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/20 14:46:22 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_line(char *line, t_shell *shell)
{
	t_token	*temp;
	char	*exp_line;

	temp = new_token(ft_strdup(line), WORD, NO_QUOTE);
	if (!temp)
		return (line);
	if (expand_token(shell, &temp) == FAILURE)
	{
		free_tokens(&temp);
		return (line);
	}
	if (temp->expand_tokens)
	{
		exp_line = merge_tokens_to_str(temp->expand_tokens);
	}
	else
		exp_line = ft_strdup(line);
	free_tokens(&temp);
	free(line);
	return (exp_line);
}

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
			return (1);
		}
		if (ft_strncmp(line, eof, (ft_strlen(eof) + 1)) == SUCCESS)
		{
			free(line);
			return (0);
		}
		if (expand == TRUE)
			line = expand_line(line, shell);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static	int	expand_heredoc(t_token *eof)
{
	while (eof)
	{
		if (eof->quote != NO_QUOTE)
			return (FALSE);
		eof = eof->next;
	}
	return (TRUE);
}

int	open_heredoc(t_redir *heredoc, t_shell *shell)
{
	int		fd;
	t_token	*eof;
	char	*eof_str;
	int		expand;

	eof = heredoc->file_tokens;
	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == ERROR)
		return (put_error(OPEN, "heredoc", shell), ERROR);
	expand = expand_heredoc(eof);
	eof_str = merge_tokens_to_str(eof);
	if (!eof_str)
	{
		unlink("/tmp/.heredoc");
		close(fd);
		return (put_error(MALLOC, "heredoc", shell), ERROR);
	}
	set_signals(SIG_HEREDOC);
	read_heredoc(fd, expand, eof_str, shell);
	set_signals(SIG_INTERACTIVE);
	free(eof_str);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	unlink("/tmp/.heredoc");
	if (fd == ERROR)
		return (put_error(OPEN, "/tmp/.heredoc", shell), ERROR);
	return (fd);
}
