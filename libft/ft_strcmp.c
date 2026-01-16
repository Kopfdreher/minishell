/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:23:18 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/16 14:24:07 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	compare1;
	unsigned char	compare2;

	i = 0;
	while (1)
	{
		compare1 = (unsigned char)s1[i];
		compare2 = (unsigned char)s2[i];
		if (compare1 != compare2 || !compare1 || !compare2)
			return (compare1 - compare2);
		i++;
	}
	return (0);
}
