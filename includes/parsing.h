/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:10 by sgavrilo          #+#    #+#             */
/*   Updated: 2025/12/31 19:20:11 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "defines.h"

// Tokenizer
void	tokenize(t_shell *shell);
int		check_syntax(t_token *tokens);

// Expander
void	expand_variables(t_shell *shell);
void	remove_quotes(t_shell *shell);

// Parser
void	parse_cmds(t_shell *shell);
t_cmd	*create_cmd_node(void);
void	add_redir_to_cmd(t_cmd *cmd, t_token *token);

// Cleanup (Specific to Parser)
void	free_tokens(t_token **tokens);

#endif
