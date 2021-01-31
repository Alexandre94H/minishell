/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 10:23:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 20:13:35 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../utils/env.h"
#include "../utils/lib.h"

char	*get_parent(char *path)
{
	size_t	index;
	size_t	length;
	char	*parent;
	char	**split;

	split = ft_split(path, '/');
	length = 0;
	while (split[length])
		length++;
	if (!(parent = malloc(sizeof(char *))))
		return (0);
	*parent = 0;
	index = 0;
	while (index < length - 1)
	{
		ft_stradd(&parent, "/");
		ft_stradd(&parent, split[index]);
		free(split[index]);
		index++;
	}
	free(split[index + 1]);
	free(split);
	return (parent);
}

int		init_path(char *arg, char *current, char **new)
{
	char	*temp;
	int		ret;

	if (*arg == '/')
		return (0);
	if (ft_equals(arg, "..") || !ft_stristr(arg, "../"))
	{
		temp = get_parent(current);
		ft_stradd(new, temp);
		free(temp);
		return (2);
	}
	if (ft_equals(arg, ".") || !ft_stristr(arg, "./"))
		ret = 1;
	else
		ret = 0;
	ft_stradd(new, current);
	return (ret);
}

int		f_cd(char **args, char **env)
{
	char	*new;
	char	*arg;

	arg = args[1];
	if (!arg)
	{
		ft_putstr("need a path\n");
		return (1);
	}
	if (!(new = malloc(sizeof(char *))))
		return (-1);
	*new = 0;
	arg += init_path(arg, env_get(env, "PWD"), &new);
	if (*arg == '/')
		arg++;
	if (*arg)
	{
		if (new[ft_strlen(new, 0) - 1] != '/')
			ft_stradd(&new, "/");
		ft_stradd(&new, arg);
	}
	chdir(new);
	env_set(env, "PWD", new);
	free(new);
	return (0);
}
