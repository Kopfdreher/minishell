/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:30:37 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/20 11:31:24 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "defines.h"

void	handler_interactive(int sig);
void	handler_heredoc(int sig);
void	set_signals(t_sig_mode	mode);

#endif
