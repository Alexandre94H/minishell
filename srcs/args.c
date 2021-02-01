/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:45:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/01 13:50:13 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../utils/lib.h"

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