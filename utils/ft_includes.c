/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_includes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:40:02 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/20 19:54:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

bool	ft_includes(char *from, char *str)
{
	size_t	index;

	while (*from)
	{
		if (*from == *str)
		{
			index = 1;
			while (str[index] && from[index] == str[index])
				index++;
			if (str[index] == 0)
				return (true);
			from += index - 1;
		}
		from++;
	}
	return (false);
}