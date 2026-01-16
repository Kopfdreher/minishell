/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:32:47 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 14:32:46 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_variable(t_shell *shell, char *arg)
{
	t_env	*new_node;

	new_node = new_env_node(arg);
	if (!new_node)
		return (FAILURE);
	add_env_node_to_back(&shell->env_list, new_node);
	return (SUCCESS);
}

static int	set_new_value(t_env *curr, char *arg)
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
		free(curr->value);
		curr->value = new_value;
		new_word_count = get_word_count(curr->value);
		new_tokens = create_env_tokens(curr->value);
		if (curr->value && new_word_count && !new_tokens)
			return (FAILURE);
		free_tokens(&curr->tokens);
		curr->tokens = new_tokens;
		curr->word_count = new_word_count;
	}
	return (SUCCESS);
}

static int	get_variable_name(char *arg, char **variable_name)
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
	char	*variable_name;
	t_env	*curr;

	if (!args || !args[0])
		return (SUCCESS);
	if (!args[1])
		return (export_print_out(shell->env_list));
	i = 0;
	while (args[++i])
	{
		if (args[i][0] == '=')
		{
			put_error(ERROR, "export: `=': not a valid identifier", shell);
			continue ;
		}
		if (get_variable_name(args[i], &variable_name) == FAILURE)
			return (FAILURE);
		curr = get_env_node(shell->env_list, variable_name);
		if (curr && set_new_value(curr, args[i]) == FAILURE)
			return (free(variable_name), FAILURE);
		if (!curr && add_new_variable(shell, args[i]) == FAILURE)
			return (free(variable_name), FAILURE);
		free(variable_name);
	}
	return (SUCCESS);
}
