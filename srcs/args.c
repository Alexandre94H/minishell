/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:45:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/24 13:38:38 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
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
	if ((*content)[index + prefix_size] == '<'
		|| (*content)[index + prefix_size] == '>')
		prefix_size++;
	if ((*content)[index + prefix_size] == '>')
		prefix_size++;
	while (ft_isspace((*content)[index + prefix_size]))
		prefix_size++;
	filename_size = 0;
	while ((*content)[index + prefix_size + filename_size]
		&& !ft_isspace((*content)[index + prefix_size + filename_size]))
		filename_size++;
	if (!prefix_size || !filename_size)
		return (-1);
	temp = ft_strndup(*content + index, prefix_size + filename_size);
	ret = arrow(temp, temp + prefix_size);
	if (ret != -1)
		ft_replace(content, index, prefix_size + filename_size, "");
	free(temp);
	return (ret);
}

char	*add_arg_loop_mark(size_t *index, char *content, char **env)
{
	bool	strict;
	size_t	index1;
	char	*part;

	strict = content[*index] == '\'';
	index1 = 1;
	while (content[*index + index1]
		&& (content[*index + index1 - 1] == '\\'
		|| content[*index + index1] != content[*index]))
		index1++;
	part = ft_strndup(content + *index + 1, index1 - 1);
	if (!strict)
		update_str(&part, env, false);
	*index += index1 - !content[*index + index1] + 1;
	return (part);
}

char	*add_arg_loop(size_t *index, char *content, char **env)
{
	char	*part;
	size_t	index1;

	if ((!*index || content[*index - 1] != '\\')
		&& (content[*index] == '\'' || content[*index] == '"'))
		return (add_arg_loop_mark(index, content, env));
	index1 = 1;
	while (content[*index + index1]
		&& !ft_isspace(content[*index + index1])
		&& content[*index + index1] != '\''
		&& content[*index + index1] != '"')
		index1++;
	part = ft_strndup(content + *index, index1);
	update_str(&part, env, true);
	*index += index1;
	return (part);
}

size_t	add_arg(char ***args, char *content, char **env)
{
	size_t	index;
	char	*arg;
	char	*part;

	index = 0;
	while (ft_isspace(content[index]))
		index++;
	if (!content[index])
		return (index);
	if (!(arg = malloc(sizeof(char *))))
		return (0);
	*arg = 0;
	while (content[index] && !ft_isspace(content[index]))
	{
		part = add_arg_loop(&index, content, env);
		ft_addstr(part, &arg);
		free(part);
	}
	ft_addtab((void ***)args, arg);
	return (index);
}

char	**split_args(char **content, char **env)
{
	size_t	index;
	size_t	ret;
	char	**args;

	index = -1;
	ret = 0;
	while (!ret && (*content)[++index])
		if ((*content)[index] == '<' || (*content)[index] == '>')
			ret = remove_arrow(content, index--);
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
	while ((ret && (*content)[index]) || !*args)
		index += (ret = add_arg(&args, (*content) + index, env));
	return (args);
}
