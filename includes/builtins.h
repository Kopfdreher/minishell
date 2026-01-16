/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:33 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 20:32:27 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "defines.h"

// echo
int	ft_echo(char **args);

// cd
int	ft_cd(char **args, t_shell *shell);

// pwd
int	ft_pwd(t_shell *shell);

// export
int	ft_export(t_shell *shell, char **args);
int	export_print_out(t_env	*env_list);
int	add_new_variable(t_env	**env_list, char *arg);
int	set_new_value(t_env *curr, char *arg);
int	get_variable_name(char *arg, char **variable_name);

// unset
int	ft_unset(t_shell *shell, char **args);

// env
int	ft_env(t_shell *shell);
int	env_parameter_shift(char ***args);

// exit
int	ft_exit(t_shell *shell, char **args);

// Helper to check/run
int	is_builtin(t_cmd *cmd);
int	exec_builtin(t_cmd *cmd, t_shell *shell);

#endif
