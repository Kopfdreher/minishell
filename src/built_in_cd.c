/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:41:28 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/16 16:25:02 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, t_shell *shell)
{
	char	*dir;

	dir = NULL;
	if (!args)
		return (FAILURE);
	if (args[1] && args[2])
	{
		put_error(CD, "too many arguments\n", shell);
		return (FAILURE);
	}
	if (args[1] == FALSE || ft_strncmp(args[1], "~", 2) == 0)
		dir = getenv("HOME");
	else
		dir = args[1];
	if (chdir(dir) == ERROR)
	{
		put_error(CHDIR, "cd", shell);
		return (FAILURE);
	}
	return (SUCCESS);
}
