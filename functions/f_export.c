/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:39:24 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/28 20:11:59 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utils/lib.h"
#include "../utils/env.h"

static void	print_env(char **env)
{
	char	**sort;
	char	*temp;
	char	*value;
	size_t	index;
	size_t	index1;
	bool	edit;

	index = 0;
	while (env[index])
		index++;
	if (!(sort = malloc(sizeof(char **) * (index + 1))))
		return ;
	sort[index] = 0;
	while (index--)
		sort[index] = env[index];
	edit = true;
	while (edit)
	{
		edit = false;
		index = 0;
		while (sort[index + 1])
		{
			index1 = 0;
			while (sort[index][index1]
				&& sort[index][index1] == sort[index + 1][index1])
				index1++;
			if (sort[index][index1] > sort[index + 1][index1])
			{
				edit = true;
				temp = sort[index];
				sort[index] = sort[index + 1];
				sort[index + 1] = temp;
			}
			index++;
		}
	}
	index = -1;
	while (sort[++index])
		if (*(sort[index]) != '_')
		{
			index1 = ft_strlen(sort[index], '=');
			temp = ft_strndup(sort[index], index1);
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(temp, 1);
			if (sort[index][index1])
			{
				ft_putstr_fd("=\"", 1);
				value = env_get(env, temp);
				index1 = 0;
				while (value[index1])
				{
					if (value[index1] == '"'
						|| value[index1] == '$'
						|| value[index1] == '\\')
						ft_putchar_fd('\\', 1);
					ft_putchar_fd(value[index1++], 1);
				}
				ft_putchar_fd('"', 1);
			}
			ft_putchar_fd('\n', 1);
			free(temp);
		}
	free(sort);
}

bool		export_loop(char *arg, char **env)
{
	size_t	index;
	bool	right;
	char	*temp;

	index = 0;
	right = ft_isalnum(arg[index]);
	while (arg[index] && ft_isalnum(arg[index]))
		index++;
	if (arg[index] && arg[index] != '=')
		right = false;
	index = ft_strlen(arg, '=');
	temp = ft_strndup(arg, index);
	if (!right)
	{
		ft_putchar_fd('`', 1);
		ft_putstr_fd(temp, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
	}
	else if (arg[index])
		env_set(env, temp, arg + index + 1);
	else
		env_set(env, temp, 0);
	free(temp);
	return (right);
}

char		f_export(char **args, char **env)
{
	size_t	index;
	char	ret;

	ret = 0;
	if (!args[1])
		print_env(env);
	else
	{
		index = 1;
		while (args[index])
		{
			if (!export_loop(args[index], env))
				ret = 1;
			index++;
		}
	}
	return (ret);
}
