/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/02 22:25:38 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
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
	ft_putstr_fd("\n\e[0m$ ", 1);
}

int		input(char **line)
{
	int		ret;
	size_t	index;

	ret = get_next_line(0, line);
	if (!ret && **line)
		while (ret == 0)
		{
			free(*line);
			ret = get_next_line(0, line);
		}
	if (ret && !**line)
		ft_putstr_fd("$ ", 1);
	else
	{
		index = 0;
		while ((*line)[index] && ft_isspace((*line)[index]))
			index++;
		if (!(*line)[index])
			**line = 0;
	}
	sig();
	return (ret);
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
		ret = input(&line);
		if (ret && *line)
		{
			ret = !right_syntax(line) || !dispatch(line, env);
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
