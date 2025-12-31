/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:23 by sgavrilo          #+#    #+#             */
/*   Updated: 2025/12/31 19:20:25 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "defines.h"

// Main Loop
void	execute_cmds(t_shell *shell);
void	wait_for_children(t_shell *shell);

// Logic
char	*find_path(char *cmd, char **env);
void	handle_pipes(t_cmd *cmd);
int		check_heredocs(t_shell *shell);

// Redirection
int		apply_redirections(t_cmd *cmd);
void	close_fds(t_cmd *cmd);

// Signals
void	setup_signals(int mode);

// Cleanup (Executer specific)
void	free_cmds(t_cmd **cmds);
void	free_env_array(char **array);

#endif
