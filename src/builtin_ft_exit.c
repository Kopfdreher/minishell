/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:17:44 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 20:55:43 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_invalid_code(char *code)
{
	int	i;

	i = 0;
	if (code[i] == '+' || code[i] == '-')
		i++;
	if (!code[i])
		return (TRUE);
	while (code[i])
	{
		if (ft_isdigit(code[i]) == FALSE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_exit(char **args, t_shell *shell)
{
	char	*errorstr;

	if (!args[1])
		shell->exit_status = 0;
	else if (is_invalid_code(args[1]) == TRUE)
	{
		errorstr = ft_strjoin(args[1], ": numeric argument required\n");
		put_error(EXIT, errorstr, shell);
		free(errorstr);
		shell->exit_status = 2;
	}
	else if (args[2])
	{
		put_error(EXIT, "too many arguments\n", shell);
		shell->exit_status = 1;
		return (1);
	}
	else
		shell->exit_status = ft_atoi(args[1]);
	shell->running = FALSE;
	return (shell->exit_status);
}
