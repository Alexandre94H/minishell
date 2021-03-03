/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:31:05 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:58:59 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"

int		remove_arrow(char **content, size_t index, char **env)
{
	size_t	prefix_size;
	size_t	filename_size;
	char	*filename;
	int		ret;

	prefix_size = 1;
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
	update_content(&filename);
	ret = arrow(*content + index, filename);
	free(filename);
	if (!ret)
		ft_replace(content, index, prefix_size + filename_size, "");
	return (ret);
}

bool	update_arrow(char **content, char **env)
{
	size_t	index;
	int		ret;

	index = 0;
	ret = 0;
	while (!ret && (*content)[index])
		if ((*content)[index] == '\'' || (*content)[index] == '"')
			index += skip_quote(*content + index);
		else if (((*content)[index] == '<' || (*content)[index] == '>')
			&& (!index || (*content)[index - 1] != '\\'))
			ret = remove_arrow(content, index, env);
		else
			index++;
	if (ret)
	{
		ft_putstr_fd("error while loading file\n", 2);
		return (false);
	}
	return (true);
}
