/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 10:02:37 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/21 10:07:22 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_freetab(void ***tab)
{
	size_t	index;

	index = 0;
	while ((*tab)[index])
		free((*tab)[index++]);
	free(*tab);
}
