/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:12:10 by sgavrilo          #+#    #+#             */
/*   Updated: 2025/12/31 20:12:46 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZE_H
# define INITIALIZE_H

# include "defines.h"

void	init_shell(t_shell *shell, char **envp);
t_env	*init_env(char **envp);
void	free_env_list(t_env **env_list);

#endif
