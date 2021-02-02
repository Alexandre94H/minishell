/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:45:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/02 16:38:19 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include "../utils/lib.h"
#include "../utils/env.h"

void	add_env(char **str, char **env)
{
	size_t	index;
	size_t	index1;
	char	*name;
	char	*key;

	index = 0;
	while (env[index])
	{
		name = ft_strndup(env[index], ft_strlen(env[index], '='));
		index1 = ft_strlen(name, 0);
		index1++;
		if (!(key = malloc(sizeof(char *) * (index1 + 1))))
			return ;
		key[index1] = 0;
		*key = '$';
		index1 = 0;
		while (name[index1])
		{
			key[index1 + 1] = name[index1];
			index1++;
		}
		ft_replace(str, key, env_get(env, name));
		free(key);
		free(name);
		index++;
	}
	ft_replace(str, "$?", ft_itoa(errno));
}

char	*arg_no_null(char *arg, size_t length, char **env)
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
	if (env)
		add_env(&ret, env);
	return (ret);
}

size_t	fill_args(char *content, char **args, char **env)
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
				args[length] = arg_no_null(content, index, env);
			length++;
			content += index + 1;
			index = 0;
		}
		else
			index++;
	if (args)
		args[length] = arg_no_null(content, index, env);
	free(c);
	return (length + 1);
}

char	**split_args(char *content, char **env)
{
	char	**args;
	char	*clone;
	size_t	length;

	clone = ft_strndup(content, 0);
	length = fill_args(clone, 0, 0);
	free(clone);
	if (!(args = malloc(sizeof(char **) * (length + 1))))
		return (0);
	args[length] = 0;
	fill_args(content, args, env);
	return (args);
}
