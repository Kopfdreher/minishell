/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 20:01:11 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 21:47:16 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_memset(shell, 0, sizeof(t_shell));
	shell->env_list = init_env(envp);
	if (!shell->env_list)
		return (put_error(MALLOC, NULL, shell), FAILURE);
	shell->env_array = NULL;
	if (execute_env_list_to_strarr(shell) == FAILURE)
		return (put_error(MALLOC, NULL, shell), FAILURE);
	shell->running = TRUE;
	return (SUCCESS);
}

void	free_heredocs_lst(t_list **lst)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

void	print_heredocs(t_shell *shell)
{
	t_list	*curr;
	t_redir	*curr_redir;

	curr = shell->heredocs;
	while (curr)
	{
		curr_redir = curr->content;
		if (curr_redir && curr_redir->file)
			ft_printf("%s\n", curr_redir->file);
		curr = curr->next;
	}
}
