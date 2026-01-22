/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:49:54 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 16:10:32 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	path_from_dirs(char **dirs, char **cmd, char **path)
{
	size_t	i;
	size_t	n;

	i = 0;
	while (dirs && dirs[i])
	{
		n = ft_strlen(dirs[i]) + 1 + ft_strlen(*cmd) + 1;
		*path = malloc(n);
		if (!*path)
			return (ERROR);
		ft_strlcpy(*path, dirs[i], n);
		ft_strlcat(*path, "/", n);
		ft_strlcat(*path, *cmd, n);
		if (access(*path, X_OK) == 0)
			return (SUCCESS);
		free(*path);
		*path = NULL;
		i++;
	}
	return (FAILURE);
}

static int	access_check(t_cmd *cmd)
{
	if (access(cmd->args[0], F_OK) == 0)
	{
		if (access(cmd->args[0], X_OK) == 0)
		{
			cmd->path = ft_strdup(cmd->args[0]);
			return (SUCCESS);
		}
		return (126);
	}
	cmd->path = NULL;
	return (127);
}

int	handle_path_ret(int ret, t_shell *shell, t_cmd *cmd)
{
	char	*errorstr;

	if (ret == ERROR)
		return (put_error(MALLOC, "minishell:", shell), 1);
	if (ret == FAILURE)
	{
		errorstr = ft_strjoin(cmd->args[0], ": command not found\n");
		if (!errorstr)
			return (put_error(MALLOC, "minishell:", shell), 1);
		put_error(CMD, errorstr, shell);
		free(errorstr);
		return (127);
	}
	put_error(PATH, cmd->args[0], shell);
	if (ret == 127)
		return (127);
	return (126);
}

int	find_path(t_cmd *cmd, t_env *env_list)
{
	char		**dirs;
	int			i;
	const char	*path_value;
	int			ret;

	if (!cmd || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
		return (cmd->path = NULL, FAILURE);
	if (ft_strchr(cmd->args[0], '/'))
		return (access_check(cmd));
	path_value = get_env_value(env_list, "PATH");
	if (!path_value)
		return (cmd->path = NULL, FAILURE);
	dirs = ft_split(path_value, ':');
	if (!dirs)
		return (cmd->path = NULL, ERROR);
	ret = path_from_dirs(dirs, cmd->args, &cmd->path);
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (ret);
}
