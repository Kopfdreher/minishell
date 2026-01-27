/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:41:28 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 15:48:48 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_pwd(char *pwd, t_shell *shell)
{
	char	*cwd;
	char	*cwd_str;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		cwd = ft_strdup(get_env_value(shell->env_list, "PWD"));
		if (cwd == NULL)
			return (put_error(MALLOC, "", shell), FAILURE);
	}
	cwd_str = ft_strjoin(pwd, cwd);
	free(cwd);
	if (cwd_str == NULL)
	{
		put_error(MALLOC, "", shell);
		return (FAILURE);
	}
	if (set_env_node(&shell->env_list, cwd_str) == FAILURE)
	{
		free(cwd_str);
		return (FAILURE);
	}
	free(cwd_str);
	return (SUCCESS);
}

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
	if (set_pwd("OLDPWD=", shell) == FAILURE)
		return (FAILURE);
	if (chdir(dir) == ERROR)
	{
		put_error(CHDIR, "cd", shell);
		return (FAILURE);
	}
	if (set_pwd("PWD=", shell) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
