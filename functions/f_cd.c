/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 10:23:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 11:33:46 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../utils/env.h"
#include "../utils/lib.h"

int	f_cd(char **args, char **env)
{
	char	*current;
	char	*new;
	char	**split;
	size_t	index;
	size_t	length;
	
	current = env_get(env, "PWD");
	if (!args[1])
	{
		ft_putstr("need a path\n");
		return (1);
	}
	if (!(new = malloc(sizeof(char *))))
		return (-1);
	*new = 0;
	if (*args[1] == '/')
		ft_stradd(&new, args[1]);
	if (ft_equals(args[1], "..") || !ft_stristr(args[1], "../"))
	{
		split = ft_split(current, '/');
		length = 0;
		while (split[length])
			length++;
		index = 0;
		while (index < length - 1)
		{
			if (index)
				ft_stradd(&new, "/");
			ft_stradd(&new, split[index]);
			free(split[index]);
			index++;
		}
		free(split[index + 1]);
		free(split);
		args[1] += 2;
	}
	else
	{
		if (ft_equals(args[1], ".") || !ft_stristr(args[1], "./"))
			args[1]++;
		ft_stradd(&new, current);
	}
	if (*args[1] == '/')
		args[1]++;
	if (*args[1])
	{
		ft_stradd(&new, "/");
		ft_stradd(&new, args[1]);
	}
	chdir(new);
	env_set(env, "PWD", new);
	free(new);
	return (0);
}