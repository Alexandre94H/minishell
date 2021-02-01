/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/01 13:42:29 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "default.h"
#include "utils/lib.h"

char	*arg_no_null(char *arg, size_t length)
{
	char	*ret;
	size_t	index;
	size_t	amount;

	amount = 0;
	index = 0;
	while (index + amount < length)
		if (!arg[index + amount])
			amount++;
		else
			index++;
	if (!(ret = malloc(sizeof(char *) * (index + 1))))
		return (0);
	ret[index] = 0;
	amount = 0;
	index = 0;
	while (index + amount < length)
		if (!arg[index + amount])
			amount++;
		else
		{
			ret[index] = arg[index + amount];
			index++;
		}
	return (ret);
}

size_t	fill_args(char *content, char **args)
{
	size_t	length;
	size_t	index;
	char	*c;
	
	if (!(c = malloc(sizeof(char *) * 2)))
		return (0);
	c[1] = 0;
	length = 0;
	index = 0;
	while (content[index])
		if ((content[index] == '\'' || content[index] == '"')
			&& (!index || content[index - 1] != '\\'))
		{
			*c = content[index];
			content[index++] = 0;
			index += ft_stristr(content + index, c);
			content[index++] = 0;
		}
		else if (content[index] == ' ')
		{
			if (args)
				args[length] = arg_no_null(content, index);
			length++;
			content += index + 1;
			index = 0;
		}
		else
			index++;
	if (args)
		args[length] = arg_no_null(content, index);
	free(c);
	return (length + 1);
}

char	**split_args(char *content)
{
	char	**args;
	char	*clone;
	size_t	length;

	clone = ft_strndup(content, 0);
	length = fill_args(clone, 0);
	free(clone);
	if (!(args = malloc(sizeof(char **) * (length + 1))))
		return (0);
	args[length] = 0;
	fill_args(content, args);
	return (args);
}

int		run(char *content, char **env, int last_output)
{
	char	**args;
	size_t	index;
	int		ret;

	args = split_args(content);
	ret = call_function(args, env, last_output);
	if (ret > 255)
		ret = execute(args, env);
	index = 0;
	while (args[index])
		free(args[index++]);
	free(args);
	return (ret);
}

int		dispatch(char *content, char **env)
{
	char		**contents;
	size_t		index;
	int			ret;
	static int	last_output;

	contents = ft_split(content, ';');
	index = 0;
	while (contents[index])
	{
		ret = run(contents[index], env, last_output);
		free(contents[index++]);
		if (ret < 0)
			break ;
	}
	free(contents);
	if (ret > 255)
		ft_putstr("command not found\n");
	else if (ret < 0)
		return (-1 * (ret + 1));
	else
		last_output = ret;
	return (-1);
}
