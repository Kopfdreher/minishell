/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:23 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/13 18:48:40 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "defines.h"

// Main Loop
int		execute(t_shell *shell);
int		wait_for_children(t_shell *shell);

// Logic
int		find_path(t_cmd *cmd, t_env *env_list);
void	handle_pipes(t_cmd *cmd);
int		check_heredocs(t_shell *shell);

// Redirection
int		redirs(t_redir *redir, t_shell*shell);
void	close_fds(t_cmd *cmd);

// Signals
void	setup_signals(int mode);

// Cleanup (Executer specific)
int		execute_env_list_to_strarr(t_shell *shell);

#endif
