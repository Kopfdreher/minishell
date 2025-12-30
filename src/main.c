/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 20:37:43 by sgavrilo          #+#    #+#             */
/*   Updated: 2025/12/30 20:44:06 by alago-ga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	main(void)
{
	char	*line;

	while (-1)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		printf("%s\n", line);
		free(line);
	}
}
