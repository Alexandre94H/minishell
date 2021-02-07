/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:39:11 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/07 17:28:52 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(const char *s1, long long len)
{
	char	*s2;

	if (len == -1)
	{
		len = 0;
		while (s1[len])
			len++;
	}
	if (!(s2 = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s2[len] = 0;
	while (len--)
		s2[len] = s1[len];
	return (s2);
}
