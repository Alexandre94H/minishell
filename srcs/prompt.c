/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/22 15:23:19 by ahallain         ###   ########.fr       */
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

int		input(char **line)
{
	int	ret;

	ret = get_next_line(0, line);
	if (!ret && **line)
		while (ret == 0 || !**line)
		{
			free(*line);
			ret = get_next_line(0, line);
		}
	if (ret && !**line)
		ft_putstr_fd("$ ", 1);
	return (ret);
}

bool	right_syntax(char *content)
{
	bool		ret;
	size_t		index;

	ret = false;
	index = 0;
	while (content[index])
	{
		if (content[index] == ';'
			|| content[index] == '|')
			if (ret)
				ret = false;
			else
				break;
		else if (!ft_isspace(content[index]))
			ret = true;
		index++;
	}
	if (!ret)
		ft_putstr_fd("syntax error\n", 2);
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
			if (right_syntax(line))
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
