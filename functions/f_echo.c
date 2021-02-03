/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 22:54:30 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/03 07:28:46 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../utils/lib.h"

char	f_echo(char **args)
{
	bool	new_line;

	args++;
	new_line = true;
	if (!*args)
		return (0);
	if (ft_equals("-n", *args))
	{
		new_line = false;
		args++;
	}
	if (*args)
		ft_putstr(*args++);
	while (*args)
	{
		ft_putchar(' ');
		ft_putstr(*args++);
	}
	if (new_line)
		ft_putchar('\n');
	return (0);
}
