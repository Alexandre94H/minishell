/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:50:14 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/02 14:23:28 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lib.h"

size_t	edit_str(char *str, char *new, char *from, char *to)
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
			index1 = 0;
			while (from[index1] && str[index + index1] == from[index1])
				index1++;
			if (!from[index1])
			{
				index2 = 0;
				while (to[index2])
				{
					if (new)
						new[index + index2 + length] = to[index2];
					index2++;
				}
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

	length = edit_str(*str, 0, from, to);
	if (!(new = malloc(sizeof(char **) * (length + 1))))
		return ;
	new[length] = 0;
	edit_str(*str, new, from, to);
	free(*str);
	*str = new;
}