/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:39:24 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 11:55:13 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../utils/lib.h"
#include "../utils/env.h"

int	f_export(char **args, char **env)
{
	size_t	key_length;
	char	*key;
	char	*value;

	if (!args[1])
	{
		ft_putstr("need something to export");
		ft_putchar('\n');
		return (1);
	}
	key_length = ft_strlen(args[1], '=');
	key = ft_strndup(args[1], key_length);
	value = ft_strndup(args[1] + key_length + 1, 0);
	env_set(env, key, value);
	free(key);
	free(value);
	return (0);
}