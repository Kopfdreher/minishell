/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:22:25 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/13 20:50:17 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_error_type(t_error_type type)
{
	if (type == SYNTAX)
		return ("syntax error near unexpected token ");
	else if (type == PIPES)
		return ("pipe() failed\n");
	else if (type == FORK)
		return ("fork() failed\n");
	else if (type == DUP2)
		return ("dup2() failed\n");
	else if (type == OPEN)
		return ("open() failed\n");
	else if (type == H_DOC)
		return ("warning: here-document delimited by end-of-file (wanted: `");
	else if (type == PATH)
		return ("");
	else if (type == EXECVE)
		return ("");
	return ("");
}

static int	get_error_num(t_error_type type)
{
	if (type == SYNTAX)
		return (2);
	if (type == MALLOC || type==PIPES || type == FORK || type == DUP2 || type == OPEN)
		return (1);
	if (type == EXECVE)
		return (126);
	return (0);
}

void	put_error(t_error_type type, const char *str, t_shell *shell)
{
	ft_putstr_fd(get_error_type(type), 2);
	ft_putstr_fd(str, 2);
	shell->exit_status = get_error_num(type);
}
