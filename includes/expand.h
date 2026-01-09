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

t_env	*new_env_node(char *str);
void	env_print(t_env *env);
char	*get_env_value(t_env *env_list, char *name);
t_env	*get_env_node(t_env *env_list, char *name);

#endif
