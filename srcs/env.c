/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:45:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/21 21:02:37 by ahallain         ###   ########.fr       */
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
	char	*value;

	index1 = 0;
	if ((*str)[index] == '?')
		index1++;
	else
		while (ft_isalnum((*str)[index + index1])
			|| (*str)[index + index1] == '_')
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
			&& (*str)[index + 1]
			&& !ft_isspace((*str)[index + 1]))
		{
			env_loop(index + 1, str, env);
			if (!(*str)[index] || (*str)[index] == '$')
				index--;
		}
		index++;
	}
}
