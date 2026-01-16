/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:22:25 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 20:45:13 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_error_type(t_error_type type)
{
	if (type == SYNTAX)
		return ("syntax error near unexpected token ");
	else if (type == H_DOC)
		return ("warning: here-document delimited by end-of-file (wanted: `");
	else if (type == PATH)
		return ("");
	else if (type == CD)
		return ("cd: ");
	return ("");
}

static int	is_system_error(t_error_type type)
{
	if (type == PIPES || type == MALLOC || type == FORK 
		|| type == DUP2 || type == OPEN || type == EXECVE || type == CHDIR)
		return (TRUE);
	else
		return (FALSE);
}

static int	get_error_num(t_error_type type)
{
	if (type == SYNTAX)
		return (2);
	if (type == MALLOC || type == PIPES || type == FORK
		|| type == DUP2 || type == OPEN || type == CD || type == CHDIR)
		return (1);
	if (type == EXECVE)
		return (126);
	return (0);
}

void	put_error(t_error_type type, const char *str, t_shell *shell)
{
	if (is_system_error(type) == TRUE)
		perror(str);
	else
	{
		ft_putstr_fd(get_error_type(type), 2);
		ft_putstr_fd(str, 2);
	}
	shell->exit_status = get_error_num(type);
}
