/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 22:54:30 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 23:12:26 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../utils/lib.h"

int	f_echo(char **args)
{
	bool	new_line;

	args++;
	new_line = true;
	if (*args)
	{
		if (ft_equals("-n", *args))
			new_line = false;
		else
			ft_putstr(*args);
		args++;
	}
	while (*args) {
		ft_putchar(' ');
		ft_putstr(*args++);
	}
	if (new_line)
		ft_putchar('\n');
	return (0);
}
