/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:31:05 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/27 18:52:21 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"

int		remove_arrow(char **content, size_t index, char **env)
{
	size_t	prefix_size;
	size_t	filename_size;
	char	*filename;
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
		&& ((*content)[index + prefix_size + filename_size - 1] == '\\'
		|| !ft_isspace((*content)[index + prefix_size + filename_size])))
		filename_size++;
	filename = ft_strndup(*content + index + prefix_size, filename_size);
	update_env(&filename, env);
	ret = arrow(*content + index, filename);
	free(filename);
	if (ret != -1)
		ft_replace(content, index, prefix_size + filename_size, "");
	return (ret);
}

void	update_arrow(char **content, char **env)
{
	size_t	index;

	index = 0;
	while ((*content)[index])
		if (((*content)[index] == '<' || (*content)[index] == '>')
			&& (!index || (*content)[index - 1] != '\\'))
			remove_arrow(content, index, env);
		else
			index++;
}
