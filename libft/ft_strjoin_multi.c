/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_multi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgavrilo <sgavrilo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:35:06 by sgavrilo          #+#    #+#             */
/*   Updated: 2026/01/20 11:08:56 by sgavrilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_total_len(size_t count, va_list *args)
{
	char	*curr_str;
	size_t	total_len;
	size_t	i;

	total_len = 0;
	i = 0;
	va_arg(*args, size_t);
	while (i < count)
	{
		curr_str = va_arg(*args, char *);
		if (curr_str)
			total_len += ft_strlen(curr_str);
		else
			return (-1);
		i++;
	}
	return (total_len);
}

static void	cpy_args_into_str(size_t count, va_list *args, char *joined_str)
{
	char	*curr_str;
	size_t	i;
	size_t	len;
	size_t	curr_pos;

	curr_pos = 0;
	i = 0;
	va_arg(*args, size_t);
	while (i < count)
	{
		curr_str = va_arg(*args, char *);
		if (curr_str)
		{
			len = ft_strlen(curr_str);
			ft_memcpy(&joined_str[curr_pos], curr_str, len);
			curr_pos += len;
		}
		i++;
	}
}

/* returns NULL if one of the args is NULL,
 * so allocations in the args are recognized */
char	*ft_strjoin_multi(size_t count, ...)
{
	va_list	args;
	char	*joined_str;
	int		len;

	va_start(args, count);
	len = get_total_len(count, &args);
	if (len == -1)
		return (NULL);
	va_end(args);
	joined_str = ft_calloc(len + 1, sizeof(char));
	if (!joined_str)
		return (NULL);
	va_start(args, count);
	cpy_args_into_str(count, &args, joined_str);
	va_end(args);
	return (joined_str);
}
