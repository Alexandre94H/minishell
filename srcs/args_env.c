/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:27:34 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/02 19:16:04 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"

char	*env_space(char *str)
{
	size_t	index;
	size_t	index1;
	char	*value;

	index1 = 0;
	index = 0;
	if (str[index])
		while (str[++index])
			if (str[index - 1] == ' ' && str[index] == ' ')
				index1++;
	if (!(value = malloc(sizeof(char *) * (index - index1 + 1))))
		return (NULL);
	value[index - index1] = 0;
	index1 = 0;
	index = -1;
	while (str[++index])
		if (index && str[index - 1] == ' ' && str[index] == ' ')
			index1++;
		else
			value[index - index1] = str[index];
	return (value);
}

void	env_loop(size_t *index, char **str, char **env)
{
	size_t	index1;
	char	*name;
	char	*value;

	index1 = 0;
	if ((*str)[*index] == '?' || (*str)[*index] == '_')
		index1++;
	else
		while ((*str)[*index + index1]
			&& ft_isalnum((*str)[*index + index1]))
			index1++;
	if ((*str)[*index] == '?')
	{
		value = ft_itoa(errno);
		ft_replace(str, *index - 1, index1 + 1, value);
	}
	else
	{
		name = ft_strndup(*str + *index, index1);
		value = env_space(env_get(env, name));
		free(name);
		ft_replace(str, *index - 1, index1 + 1, value);
	}
	*index += ft_strlen(value, 0) - 1;
	free(value);
}
