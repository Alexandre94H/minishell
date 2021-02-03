/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/03 09:08:48 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"
#include "../utils/get_next_line.h"

void	prompt_header(char **env)
{
	ft_putstr("\e[93m");
	ft_putstr(env_get(env, "LOGNAME"));
	ft_putstr("\e[0m in \e[95m");
	ft_putstr(env_get(env, "PWD"));
	ft_putstr("\e[0m with exit code ");
	if (errno)
		ft_putstr("\e[91m");
	else
		ft_putstr("\e[92m");
	ft_putnbr(errno);
	ft_putchar('\n');
}

int		prompt(char **env)
{
	int		ret;
	char	*line;

	ret = 0;
	prompt_header(env);
	while (!ret)
	{
		ft_putstr("\e[0m$ ");
		ret = !get_next_line(2, &line);
		if (*line)
			ret = dispatch(line, env);
		ft_putchar('\n');
		if (*line && !ret)
			prompt_header(env);
		free(line);
	}
	return (errno);
}
