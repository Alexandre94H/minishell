/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:45:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/21 19:26:39 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"

void	env_loop(size_t index, char **str, char **env)
{
	size_t	index1;
	char	*key;

	index1 = 0;
	if ((*str)[index + index1] == '?')
		index1++;
	else
		while (ft_isalnum((*str)[index + index1])
			|| (*str)[index + index1] == '_')
			index1++;
	if (!index1)
		return ;
	key = ft_strndup(*str + index, index1);
	if (ft_equals(key, "?"))
	{
		free(key);
		key = ft_itoa(errno);
		ft_replace(str, index - 1, index1 + 1, key);
	}
	else if (ft_strlen(key, 0))
		ft_replace(str, index - 1, index1 + 1, env_get(env, key));
	free(key);
}

void	update_str(char **str, char **env, bool force_slash)
{
	size_t	index;

	index = 0;
	while ((*str)[index])
	{
		if ((*str)[index] == '\\' && (force_slash
			|| !ft_isspace((*str)[index + 1])))
		{
			ft_rmchar(str, index);
			if (!(*str)[index])
				index--;
		}
		else if ((*str)[index] == '$'
			&& ft_isalnum((*str)[index + 1]))
		{
			env_loop(index + 1, str, env);
			if (!(*str)[index] || (*str)[index] == '$')
				index--;
		}
		index++;
	}
}
