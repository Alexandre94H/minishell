/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addtab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:03:36 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/21 19:54:11 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	**ft_addtab(void ***tab, void *str)
{
	size_t	index;
	size_t	length;
	void	**new;

	length = 0;
	while ((*tab)[length])
		length++;
	if (!(new = malloc(sizeof(*tab) * (length + 2))))
		return (NULL);
	new[length + 1] = 0;
	new[length] = str;
	index = 0;
	while (index < length)
	{
		new[index] = (*tab)[index];
		index++;
	}
	free(*tab);
	*tab = new;
	return (*tab);
}
