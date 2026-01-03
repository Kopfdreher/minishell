/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:10 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/03 16:52:48 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "defines.h"

// tokenize_shell
void	tokenize(t_shell *shell);

// tokenize_helper
t_token	*new_token(char	*value, t_token_type token, t_quote_type quote);
void	add_token_back(t_token **head, t_token **tail, t_token *new_node);
void	free_tokens(t_token **tokens);

// tokenize_print
void	print_tokens(t_token *tokens);

// tokenize_syntax
int		check_syntax(t_shell *shell, t_token *tokens);

//tokenize_word
int		add_word_token(t_shell *shell, t_token **last_token, int *i);

// Expander
void	expand_variables(t_shell *shell);
void	remove_quotes(t_shell *shell);

// Parser
void	parse_cmds(t_shell *shell);
t_cmd	*create_cmd_node(void);
void	add_redir_to_cmd(t_cmd *cmd, t_token *token);

#endif
