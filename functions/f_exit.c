/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/06 12:43:12 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../utils/lib.h"

char	f_exit(char **args)
{
	if (args[1])
	{
		errno = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putstr_fd("too many arguments\n", 2);
			return (1);
		}
	}
	return (-1);
}
