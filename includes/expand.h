/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 19:20:10 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/03 22:05:57 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "defines.h"

//t_env	*new_env_node(char *str);
void	env_print(t_env *env);
char	*get_env_value(t_env *env_list, char *name);
t_env	*get_env_node(t_env *env_list, char *name);
t_token	*get_env_tokens(t_env *env_list, char *name);
int		is_variable_separator(char c);
int		add_expanded_exit_code(t_token **token, int *i, int exit_code);
int		expand_token(t_shell *shell, t_token **token);
int		expand_token_list(t_shell *shell);
int		add_expanded_str(t_token **token, int *i, t_env *env_list);
int		add_expanded_tokens(t_token **token, int *i, t_env *env_list);
int		copy_token_list(t_token *variable_tokens, t_token **copy_head);
int		expand_args_list_to_strarr(t_arg *args_list, char ***strarr);

#endif
