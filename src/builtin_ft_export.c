/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:32:47 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 16:54:23 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_new_variable(t_env	**env_list, char *arg)
{
	t_env	*new_node;

	new_node = new_env_node(arg);
	if (!new_node)
		return (FAILURE);
	add_env_node_to_back(env_list, new_node);
	return (SUCCESS);
}

int	set_new_value(t_env *curr, char *arg)
{
	int		start;
	char	*new_value;
	t_token	*new_tokens;
	int		new_word_count;

	start = 0;
	while (arg[start] && arg[start] != '=')
		start++;
	if (arg[start])
	{
		start++;
		new_value = ft_strdup(&arg[start]);
		if (!new_value)
			return (FAILURE);
		new_word_count = get_word_count(new_value);
		new_tokens = create_env_tokens(new_value);
		if (new_word_count && !new_tokens)
			return (free(new_value), FAILURE);
		free(curr->value);
		free_tokens(&curr->tokens);
		curr->value = new_value;
		curr->tokens = new_tokens;
		curr->word_count = new_word_count;
	}
	return (SUCCESS);
}

int	get_variable_name(char *arg, char **variable_name)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	*variable_name = ft_substr(arg, 0, len);
	if (!*variable_name)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_export(t_shell *shell, char **args)
{
	int		i;

	if (!args || !args[0])
		return (SUCCESS);
	if (!args[1])
		return (export_print_out(shell->env_list));
	i = 0;
	while (args[++i])
	{
		if (args[i][0] == '=') // add: is_valid_identifier(args[i]) == FALSE
		{
			put_error(ERROR, "export: not a valid identifier", shell);
			continue ;
		}
		if (set_env_node(&shell->env_list, args[i]) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
