/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:03:49 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 11:48:05 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "lib.h"

char	*env_get(char **env, char *key)
{
	char	*name;
	bool	equal;

	while (*env)
	{
		name = ft_strndup(*env, ft_strlen(*env, '='));
		equal = ft_equals(name, key);
		free(name);
		if (equal)
			return (*env + ft_strlen(*env, '=') + 1);
		env++;
	}
	return ("");
}

char	*env_set(char **env, char *key, char *value)
{
	size_t	index;
	char	*name;
	bool	equal;
	size_t	length;
	char	**new_env;

	index = 0;
	while (env[index])
	{
		name = ft_strndup(env[index], ft_strlen(env[index], '='));
		equal = ft_equals(name, key);
		free(name);
		if (equal)
			break;
		index++;
	}
	if (!env[index])
	{
		length = index;
		if (!(new_env = malloc(sizeof(char **) * (length + 2))))
			return (0);
		env[length + 1] = 0;
		index = -1;
		while (++index < length)
			new_env[index] = env[index];
	}
	else
		free(env[index]);
	if (!(env[index] = malloc(sizeof(char *))))
		return (0);
	*(env[index]) = 0;
	ft_stradd(&env[index], key);
	ft_stradd(&env[index], "=");
	ft_stradd(&env[index], value);
	return (env[index]);
}