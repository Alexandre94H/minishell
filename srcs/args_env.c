/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:27:34 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/28 16:34:24 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"

void	env_loop(size_t index, char **str, char **env)
{
	size_t	index1;
	char	*value;

	index1 = 0;
	if ((*str)[index] == '?')
		index1++;
	else if ((*str)[index] == '_')
		index1++;
	else
		while ((*str)[index + index1]
			&& ft_isalnum((*str)[index + index1]))
			index1++;
	if ((*str)[index] == '?')
	{
		value = ft_itoa(errno);
		ft_replace(str, index - 1, index1 + 1, value);
	}
	else
	{
		value = ft_strndup(*str + index, index1);
		ft_replace(str, index - 1, index1 + 1, env_get(env, value));
	}
	free(value);
}

void	update_env(char **content, char **env)
{
	size_t	index;

	index = 0;
	while ((*content)[index])
		if ((*content)[index] == '\''
			&& (!index || (*content)[index - 1] != '\\'))
		{
			index++;
			while ((*content)[index] && (*content)[index] != '\'')
				index++;
			if ((*content)[index])
				index++;
		}
		else if ((*content)[index] == '$')
			if (index && (*content)[index - 1] == '\\')
				ft_rmchar(content, index - 1);
			else if ((*content)[index + 1]
				&& ft_isalnum((*content)[index + 1]))
				env_loop(index + 1, content, env);
			else
				index++;
		else
			index++;
}
