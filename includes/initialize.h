/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:12:10 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/26 20:31:42 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZE_H
# define INITIALIZE_H

# include "defines.h"

int		init_shell(t_shell *shell, int argc, char **argv, char **envp);
t_env	*init_env(char **envp);
void	free_env_list(t_env **env_list);
void	add_env_node_to_back(t_env **head, t_env *new_node);
void	free_heredocs_lst(t_list **lst);

#endif
