/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/14 22:59:51 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"

void	prompt_header(char **env)
{
	ft_putstr_fd("\e[93m", 1);
	ft_putstr_fd(env_get(env, "LOGNAME"), 1);
	ft_putstr_fd("\e[0m in \e[95m", 1);
	ft_putstr_fd(env_get(env, "PWD"), 1);
	ft_putstr_fd("\e[0m with exit code ", 1);
	if (errno)
		ft_putstr_fd("\e[91m", 1);
	else
		ft_putstr_fd("\e[92m", 1);
	ft_putnbr_fd(errno, 1);
	ft_putstr_fd("\n\e[0m$ ", 1);
}

void	get_line_force(char **line)
{
	int	ret;

	ret = 0;
	while (ret == 0 || !**line)
	{
		free(*line);
		ret = get_next_line(2, line);
	}
}

int		prompt(char **env)
{
	int			ret;
	char		*line;
	static int	stdin;
	static int	stdout;
	
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	prompt_header(env);
	ret = 1;
	while (ret)
	{
		ret = get_next_line(2, &line);
		if (!ret && *line)
		{
			get_line_force(&line);
			ret = 1;
		}
		if (ret && !*line)
			ft_putstr_fd("$ ", 1);
		else if (ret)
		{
			ret = !dispatch(line, env);
			dup2(stdin, STDIN_FILENO);
			dup2(stdout, STDOUT_FILENO);
			if (ret)
				prompt_header(env);
		}
		if (ret == 0)
			ft_putstr_fd("bye\n", 1);
		free(line);
	}
	return (errno);
}
