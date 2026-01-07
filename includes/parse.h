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

// Parser
int		parse(t_shell *shell);
int		add_tokens_to_cmd(t_cmd **cmd, t_token **current_token);
void	free_cmds(t_cmd **cmds);
t_cmd	*init_new_cmd(void);
void	print_cmds(t_cmd *cmd_list);
char	**args_list_to_strarr(t_arg *args_list);
char	*merge_tokens_to_str(t_token *tokens);

#endif
