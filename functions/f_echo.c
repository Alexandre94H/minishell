/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 22:54:30 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/06 11:53:23 by ahallain         ###   ########.fr       */
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
		ft_putstr_fd(*args++, 1);
	while (*args)
	{
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(*args++, 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
