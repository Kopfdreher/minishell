/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:44:43 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/23 10:50:30 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_status = 130;
	}
}

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_signal_status = 130;
		close(STDIN_FILENO);
	}
}

static void	set_sigaction_to_null(struct sigaction *sa)
{
	ft_memset(sa, 0, sizeof(sa));
	sigemptyset(&sa->sa_mask);
}

void	set_signals(t_sig_mode	mode)
{
	struct sigaction	sa;

	set_sigaction_to_null(&sa);
	if (mode == SIG_INTERACTIVE)
	{
		sa.sa_handler = handler_interactive;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_EXEC_PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == SIG_EXEC_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == SIG_HEREDOC)
	{
		sa.sa_handler = handler_heredoc;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}
