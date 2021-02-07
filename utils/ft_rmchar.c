/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:57:52 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/07 20:40:24 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	ft_rmchar(char **str, size_t index)
{
	size_t	length;
	char	*new;

	length = 0;
	while ((*str)[length])
		length++;
	if (!(new = malloc(sizeof(char *) * length--)))
		return ;
	new[length] = 0;
	while (length--)
		new[length] = (*str)[length + (length < index ? 0 : 1)];
	free(*str);
	*str = new;
}