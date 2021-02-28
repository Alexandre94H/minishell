/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/28 10:28:59 by ahallain         ###   ########.fr       */
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
	int		ret;
	size_t	index;

	ret = 0;
	while (ret == 0)
	{
		ret = get_next_line(0, line);
		if (ret != 0)
		{
			index = 0;
			while ((*line)[index] && ft_isspace((*line)[index]))
				index++;
			if (!(*line)[index])
				**line = 0;
		}
		if (ret == 0)
			free(*line);
	}
	if (!**line)
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
		if (content[index] == '\''
			|| content[index] == '"')
			index += skip_quote(content + index) - 1;
		else if (content[index] == ';'
			|| content[index] == '|')
			if (ret)
				ret = false;
			else
				break ;
		else if (content[index] == '<'
			|| content[index] == '>')
		{
			index++;
			if (content[index - 1] == '>' && content[index] == '>')
				index++;
			while (content[index] && ft_isspace(content[index]))
				index++;
			if (!content[index]
				|| content[index] == ';'
				|| content[index] == '|'
				|| content[index] == '<'
				|| content[index] == '>')
			{
				ret = false;
				break ;
			}
			index--;
		}
		else if (!ft_isspace(content[index]))
			ret = true;
		if (content[index])
			index++;
	}
	if (!content[index])
		ret = true;
	if (!ret)
	{
		ft_putstr_fd("syntax error\n", 2);
		errno = 2;
	}
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
