/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:39:24 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/02 16:08:33 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../utils/lib.h"
#include "../utils/env.h"

int	f_export(char **args, char **env)
{
	size_t	key_length;
	size_t	index;
	size_t	index1;
	char	*key;
	char	*value;

	if (!args[1])
	{
		ft_putstr("need something to export\n");
		return (1);
	}
	index = 1;
	while (args[index])
	{
		key_length = ft_strlen(args[index], '=');
		key = ft_strndup(args[index], key_length);
		index1 = -1;
		while (key[++index1])
			if (key[index1] != '_' && !ft_isalpha(key[index1]))
			{
				ft_putstr("invalid key\n");
				return (1);
			}
		value = ft_strndup(args[index] + key_length + 1, 0);
		env_set(env, key, value);
		free(key);
		free(value);
		index++;
	}
	return (0);
}
