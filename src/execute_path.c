/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:49:54 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/12 17:12:46 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*find_path_envp(char **envp)
{
	const char	*path_envp;
	int			i;

	path_envp = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (path_envp = envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*path_from_dirs(char **dirs, char **cmd)
{
	char	*path;
	size_t	i;
	size_t	n;

	i = 0;
	while (dirs && dirs[i])
	{
		n = ft_strlen(dirs[i]) + 1 + ft_strlen(*cmd) + 1;
		path = malloc(n);
		if (!path)
			return (NULL);
		ft_strlcpy(path, dirs[i], n);
		ft_strlcat(path, "/", n);
		ft_strlcat(path, *cmd, n);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(t_cmd *cmd, t_shell *shell)
{
	char		**dirs;
	char		*path;
	int			i;
	const char	*path_envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], X_OK) == 0)
			return (ft_strdup(cmd->args[0]));
		return (NULL);
	}
	path_envp = find_path_envp(shell->env_array);
	if (!path_envp)
		return (NULL);
	dirs = ft_split(path_envp, ':');
	if (!dirs)
		return (NULL);
	path = path_from_dirs(dirs, cmd->args);
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (path);
}
