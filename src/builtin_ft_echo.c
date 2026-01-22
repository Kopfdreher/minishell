/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:55:04 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 15:43:27 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_flag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (FALSE);
	i = 1;
	if (arg[i] == 0)
		return (FALSE);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (!args)
		return (FAILURE);
	while (args[i] && is_n_flag(args[i]) == TRUE)
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		print_put_string(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl == 1)
		write(1, "\n", 1);
	return (SUCCESS);
}
