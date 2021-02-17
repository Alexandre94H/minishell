/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:39:24 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/17 16:21:24 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../utils/lib.h"
#include "../utils/env.h"

char	*get_key(char *arg, size_t lengh)
{
	size_t	index;
	char	*key;

	key = ft_strndup(arg, lengh);
	index = 0;
	while (key[index])
	{
		if (!ft_isalnum(key[index]) && key[index] != '_')
		{
			ft_putstr_fd("invalid key\n", 1);
			return (NULL);
		}
		index++;
	}
	return (key);
}

char	f_export(char **args, char **env)
{
	size_t	key_length;
	size_t	index;
	char	*key;
	char	*value;

	if (!args[1])
	{
		ft_putstr_fd("need something to export\n", 2);
		return (1);
	}
	if (ft_stristr(args[1], "=") == -1)
		return (0);
	index = 1;
	while (args[index])
	{
		key_length = ft_strlen(args[index], '=');
		key = get_key(args[index], key_length);
		if (!key)
			break ;
		value = ft_strndup(args[index] + key_length + 1, -1);
		env_set(env, key, value);
		free(key);
		free(value);
		index++;
	}
	return (0);
}
