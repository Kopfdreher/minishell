/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:55:04 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/16 15:00:49 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (!args)
		return (FAILURE);
	while (args[i] && ft_strncmp(args[i], "-n", 3) == SUCCESS)
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
