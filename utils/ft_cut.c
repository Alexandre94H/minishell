/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:21:12 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 12:03:43 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lib.h"

char	**ft_cut(char *str, char c)
{
	size_t	name_len;
	char	**ret;

	name_len = ft_strlen(str, c);
	if (!(ret = malloc(sizeof(char **) * 3)))
		return (0);
	ret[0] = ft_strndup(str, name_len);
	ret[1] = ft_strndup(str + name_len + 1, 0);
	ret[2] = 0;
	return (ret);
}
