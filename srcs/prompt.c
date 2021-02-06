/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/06 08:25:51 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
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
	static int	stdin;
	static int	stdout;
	
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	prompt_header(env);
	ret = 0;
	while (!ret)
	{
		ft_putstr("\e[0m$ ");
		ret = !get_next_line(2, &line);
		if (!ret && *line)
		{
			ret = dispatch(line, env);
			dup2(stdin, STDIN_FILENO);
			dup2(stdout, STDOUT_FILENO);
			ft_putchar('\n');
			if (!ret)
				prompt_header(env);
		}
		if(ret)
			ft_putstr("Bye :D\n");
		free(line);
	}
	return (errno);
}
