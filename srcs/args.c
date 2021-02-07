/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:45:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/07 17:23:42 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"

int		remove_arrow(char **content, size_t index)
{
	size_t	prefix_size;
	size_t	filename_size;
	char	*temp;
	int		ret;

	prefix_size = 0;
	if ((*content)[index + prefix_size] == '<' || (*content)[index + prefix_size] == '>')
		prefix_size++;
	else
		return (-1);
	if ((*content)[index + prefix_size] == '>')
		prefix_size++;
	if ((*content)[index + prefix_size] == ' ')
		prefix_size++;
	filename_size = 0;
	while ((*content)[index + prefix_size + filename_size] && (*content)[index + prefix_size + filename_size] != ' ')
		filename_size++;
	if (!filename_size)
		return (-1);
	temp = ft_strndup(*content + index, prefix_size + filename_size);
	ret = arrow(temp, temp + prefix_size);
	if (ret != -1)
		ft_replace(content, temp, "");
	free(temp);
	return (ret);
}

void	add_env(char **str, char **env)
{
	size_t	index;
	size_t	index1;
	char	*key;
	char	*value;

	index = 0;
	while ((*str)[index])
		if ((*str)[index++] == '$')
		{
			index1 = 0;
			while (ft_isalnum((*str)[index + index1]) || (*str)[index + index1] == '_')
				index1++;
			if (!index1)
				continue ;
			key = ft_strndup(*str + index, index1);
			value = env_get(env, key);
			free(key);
			key = ft_strndup(*str + index - 1, index1 + 1);
			ft_replace(str, key, value);
			free(key);
		}
}

size_t	add_arg(char ***args, char *content, char **env)
{
	size_t	index;
	size_t	index1;
	char	*arg;
	char	*part;
	char	**new_args;
	bool	replace_env;

	index = 0;
	while (content[index] == ' ')
		index++;
	if (!content[index])
		return (0);
	if (!(arg = malloc(sizeof(char *))))
		return (0);
	*arg = 0;
	while (content[index] && content[index] != ' ')
	{
		if ((!index || content[index - 1] != '\\')
			&& (content[index] == '\'' || content[index] == '"'))
		{
			replace_env = content[index] == '"';
			index1 = 1;
			while (content[index + index1] && content[index + index1] != content[index])
				index1++;
			part = ft_strndup(content + index + 1, index1 - 1);
			if (replace_env)
				add_env(&part, env);
			ft_stradd(&arg, part);
			free(part);
			index += index1 + 1;
		}
		else
		{
			index1 = 1;
			while (content[index + index1] && content[index + index1] != ' ' && content[index + index1] != '\'' && content[index + index1] != '"')
				index1++;
			part = ft_strndup(content + index, index1);
			add_env(&part, env);
			ft_stradd(&arg, part);
			free(part);
			index += index1;
		}
	}
	index1 = 0;
	while ((*args)[index1])
		index1++;
	if (!(new_args = malloc(sizeof(char **) * (index1 + 2))))
		return (0);
	new_args[index1] = arg;
	new_args[index1 + 1] = 0;
	while (index1--)
		new_args[index1] = (*args)[index1];
	free(*args);
	*args = new_args;
	return (index);
}

char	**split_args(char **content, char **env)
{
	size_t	index;
	size_t	ret;
	char	**args;

	index = 0;
	ret = 0;
	while (!ret && (*content)[index])
	{
		if ((*content)[index] == '<' || (*content)[index] == '>')
			ret = remove_arrow(content, index);
		index++;
	}
	if (ret)
	{
		if ((int)ret == -1)
			ft_putstr_fd("error while loading file\n", 2);
		return (NULL);
	}
	if (!(args = malloc(sizeof(char **))))
		return (NULL);
	*args = 0;
	index = 0;
	ret = 1;
	while (ret && (*content)[index])
		index += (ret = add_arg(&args, (*content) + index, env));
	return (args);
}
