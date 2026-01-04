/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:10 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/03 22:05:57 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "defines.h"

// Expander
void	expand_variables(t_shell *shell);
void	remove_quotes(t_shell *shell);

// Parser
int		parse(t_shell *shell);
t_cmd	*create_cmd_node(void);
void	add_redir_to_cmd(t_cmd *cmd, t_token *token);

#endif
