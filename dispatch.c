/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 20:45:11 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "default.h"
#include "utils/lib.h"

size_t	fill_args(char *content, char **args)
{
	size_t	length;
	size_t	index;
	
	length = 0;
	index = 0;
	while (content[index])
		if (content[index] == ' ')
		{
			if (args)
				args[length] = ft_strndup(content, index);
			length++;
			content += index + 1;
			index = 0;
		}
		else
			index++;
	if (args)
		args[length] = ft_strndup(content, index);
	return (length + 1);
}

char	**split_args(char *content)
{
	char	**args;
	size_t	length;

	length = fill_args(content, 0);
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
