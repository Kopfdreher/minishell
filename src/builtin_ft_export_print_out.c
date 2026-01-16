/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_export_print_out.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:21:08 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 15:17:38 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	**get_ptr_envarr_to_env_list(t_env *env_list, int len)
{
	t_env	**envarr;
	int		i;

	envarr = ft_calloc(len + 1, sizeof(t_env *));
	if (!envarr)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		envarr[i] = env_list;
		env_list = env_list->next;
	}
	return (envarr);
}

static void	print_smallest(t_env ***envarr, int len)
{
	t_env	**smallest;
	int		i;

	i = -1;
	smallest = NULL;
	while (++i < len)
	{
		if (!smallest && (*envarr)[i])
			smallest = &(*envarr)[i];
		else if ((*envarr)[i] && 0 < ft_strcmp((*smallest)->name, (*envarr)[i]->name))
			smallest = &(*envarr)[i];
	}
	ft_printf("declare -x %s", (*smallest)->name);
	if ((*smallest)->value)
		ft_printf("=\"%s\"\n", (*smallest)->value);
	else
		ft_printf("\n", (*smallest)->value);
	*smallest = NULL;
}

int	export_print_out(t_env	*env_list)
{
	t_env	**envarr;
	int		len;
	int		printed;

	len = get_env_list_len(env_list);
	envarr = get_ptr_envarr_to_env_list(env_list, len);
	if (!envarr)
		return (FAILURE);
	printed = 0;
	while (printed != len)
	{
		print_smallest(&envarr, len);
		printed++;
	}
	free(envarr);
	return (SUCCESS);
}
