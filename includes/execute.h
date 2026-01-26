/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:23 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/26 22:44:30 by alago-ga         ###   ########.fr       */
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
int		handle_path_ret(int ret, t_shell *shell, t_cmd *cmd);

// Redirection
int		redirs(t_redir *redir, t_shell*shell);
void	clean_heredocs(t_shell *shell);
int		preprocess_heredocs(t_shell *shell);
int		expand_heredoc(t_token *eof);
int		read_heredoc(int fd, int expand, char *eof, t_shell *shell);
char	*expand_line(char *line, t_shell *shell);

// Cleanup (Executer specific)
int		execute_env_list_to_strarr(t_shell *shell);

#endif
