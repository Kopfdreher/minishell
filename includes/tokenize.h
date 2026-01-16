/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:16:54 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/04 13:16:56 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "defines.h"

// tokenize_shell
int		tokenize(t_shell *shell);

// tokenize_helper
t_token	*new_token(char	*value, t_token_type token, t_quote_type quote);
void	add_token_back(t_token **head, t_token **tail, t_token *new_node);
void	add_token_to_back(t_token **head, t_token *new_node);
void	free_tokens(t_token **tokens);
int		is_whitespace(char c);

// tokenize_print
void	print_tokens(t_token *tokens);

// tokenize_syntax
int		check_syntax(t_shell *shell);

//tokenize_word
int		add_word_token(t_shell *shell, t_token **last_token, int *i);
int		get_token_len(char *input, t_token *word_token);

#endif
