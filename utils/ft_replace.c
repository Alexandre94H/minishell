/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:50:14 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/03 08:43:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lib.h"

size_t	edit_str(char *new, char *to, size_t index)
{
	size_t	index1;

	index1 = 0;
	while (to[index1])
	{
		if (new)
			new[index + index1] = to[index1];
		index1++;
	}
	return (index1);
}

size_t	check_str(char *str, char *from)
{
	size_t	index;

	index = 0;
	while (from[index] && str[index] == from[index])
		index++;
	return (index);
}

size_t	replace_loop(char *str, char *new, char *from, char *to)
{
	size_t	length;
	size_t	index;
	size_t	index1;
	size_t	index2;

	length = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == *from)
		{
			index1 = check_str(str + index, from);
			if (!from[index1])
			{
				index2 = edit_str(new, to, index + length);
				index += index1;
				length += index2 - index1;
				continue ;
			}
		}
		if (new)
			new[index + length] = str[index];
		index++;
	}
	return (index + length);
}

void	ft_replace(char **str, char *from, char *to)
{
	char	*new;
	size_t	length;

	length = replace_loop(*str, 0, from, to);
	if (!(new = malloc(sizeof(char **) * (length + 1))))
		return ;
	new[length] = 0;
	replace_loop(*str, new, from, to);
	free(*str);
	*str = new;
}
