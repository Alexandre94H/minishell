/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:50:14 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:40:31 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lib.h"

void	ft_replace(char **str, size_t index, size_t length, char *to)
{
	char	*new;
	size_t	index1;
	size_t	index2;

	index1 = ft_strlen(*str, 0) + ft_strlen(to, 0) - length;
	if (!(new = malloc(sizeof(char *) * (index1 + 1))))
		return ;
	new[index1] = 0;
	index2 = 0;
	index1 = -1;
	while ((*str)[++index1])
		if (index1 == index)
		{
			while (to[index2])
			{
				new[index1 + index2] = to[index2];
				index2++;
			}
			index1 += length - 1;
			index2 -= length;
		}
		else
			new[index1 + index2] = (*str)[index1];
	free(*str);
	*str = new;
}
