/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:22:25 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/03 19:52:44 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*get_error_type(t_error_type type)
{
	if (type == SYNTAX)
		return ("minishell: syntax error near unexpected token ");
	return ("");
}

static int	get_error_num(t_error_type type)
{
	if (type == SYNTAX)
		return (2);
	return (0);
}

void	put_error(t_error_type type, const char *str, t_shell *shell)
{
	ft_putstr_fd(get_error_type(type), 2);
	ft_putstr_fd(str, 2);
	shell->exit_status = get_error_num(type);
}
