/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:33 by sgavrilo          #+#    #+#             */
/*   Updated: 2025/12/31 19:20:38 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "defines.h"

int	ft_echo(char **args);
int	ft_cd(char **args, t_env *env);
int	ft_pwd(void);
int	ft_export(t_shell *shell, char **args);
int	ft_unset(t_shell *shell, char **args);
int	ft_env(t_shell *shell);
int	ft_exit(t_shell *shell, char **args);

// Helper to check/run
int	is_builtin(char *cmd);
int	exec_builtin(t_cmd *cmd, t_shell *shell);

#endif
