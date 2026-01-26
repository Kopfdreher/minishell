/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:23:14 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/26 22:23:50 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_line(char *line, t_shell *shell)
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

static int	handle_exit(t_shell *shell, int stdin_tmp, char *eof, char *line)
{
	char	*error_string;

	if (g_signal_status != 130)
	{
		error_string = ft_strjoin(eof, "')\n");
		if (!error_string)
			return (put_error(MALLOC, "", shell), FAILURE);
		put_error(H_DOC, error_string, shell);
		return (free(error_string), free(line), SUCCESS);
	}
	if (dup2(stdin_tmp, STDIN_FILENO) == ERROR)
		return (put_error(DUP2, "", shell), ERROR);
	return (free(line), FAILURE);
}

int	read_heredoc(int fd, int expand, char *eof, t_shell *shell)
{
	char	*line;
	int		stdin_tmp;

	stdin_tmp = dup(STDIN_FILENO);
	if (stdin_tmp == ERROR)
		return (put_error(DEFAULT, "dup failed", shell), ERROR);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (handle_exit(shell, stdin_tmp, eof, line));
		if (ft_strncmp(line, eof, (ft_strlen(eof) + 1)) == SUCCESS)
			return (free(line), SUCCESS);
		if (expand == TRUE)
			line = expand_line(line, shell);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	expand_heredoc(t_token *eof)
{
	while (eof)
	{
		if (eof->quote != NO_QUOTE)
			return (FALSE);
		eof = eof->next;
	}
	return (TRUE);
}
