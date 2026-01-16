/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:49:54 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/16 20:59:49 by alago-ga         ###   ########.fr       */
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

int	find_path(t_cmd *cmd, t_env *env_list)
{
	char		**dirs;
	int			i;
	const char	*path_value;
	int			ret;

	if (!cmd || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
		return (cmd->path = NULL, FAILURE);
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], X_OK) == 0)
			return (cmd->path = ft_strdup(cmd->args[0]), SUCCESS);
		return (cmd->path = NULL, FAILURE);
	}
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
