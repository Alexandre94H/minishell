/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:21:09 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 16:28:27 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/lib.h"

int	f_exit(char **args, int last_output)
{
	if (args[1])
		last_output = ft_atoi(args[1]);
	return (-1 * (last_output + 1));
}
