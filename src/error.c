/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:22:25 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/12 17:10:40 by alago-ga         ###   ########.fr       */
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
	return ("");
}

static int	get_error_num(t_error_type type)
{
	if (type == SYNTAX)
		return (2);
	if (type == PIPES || type == FORK || type == DUP2 || type == OPEN)
		return (1);
	return (0);
}

void	put_error(t_error_type type, const char *str, t_shell *shell)
{
	ft_putstr_fd(get_error_type(type), 2);
	ft_putstr_fd(str, 2);
	shell->exit_status = get_error_num(type);
}
