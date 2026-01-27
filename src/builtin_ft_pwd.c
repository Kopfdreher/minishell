/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alago-ga <alago-ga@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:42:17 by alago-ga          #+#    #+#             */
/*   Updated: 2026/01/22 15:48:36 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		pwd = get_env_value(shell->env_list, "PWD");
		if (pwd != NULL)
		{
			ft_printf("%s\n", pwd);
			return (SUCCESS);
		}
		put_error(MALLOC, "", shell);
		return (FAILURE);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
