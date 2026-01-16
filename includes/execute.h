/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:23 by sgavrilo          #+#    #+#             */
/*   Updated: 2025/12/31 19:20:25 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "defines.h"

// Main Loop
void	execute(t_shell *shell);
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
int		execute_env_list_to_strarr(t_shell *shell);
int		get_env_list_len(t_env *env_list);

#endif
