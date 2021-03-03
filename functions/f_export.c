/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:39:24 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 13:39:15 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../srcs/default.h"
#include "../utils/lib.h"
#include "../utils/env.h"

void		print_env_value(char *value)
{
	size_t	index;

	ft_putstr_fd("=\"", 1);
	index = 0;
	while (value[index])
	{
		if (value[index] == '"'
			|| value[index] == '$'
			|| value[index] == '\\')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(value[index++], 1);
	}
	ft_putchar_fd('"', 1);
}

static void	print_env(char **env)
{
	char	**sort;
	char	*temp;
	size_t	index;
	size_t	index1;

	sort = sort_env(env);
	index = -1;
	while (sort[++index])
		if (*(sort[index]) != '_')
		{
			index1 = ft_strlen(sort[index], '=');
			temp = ft_strndup(sort[index], index1);
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(temp, 1);
			if (sort[index][index1])
				print_env_value(env_get(env, temp));
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
	right = (arg[index] >= 'A' && arg[index] <= 'Z')
		|| (arg[index] >= 'a' && arg[index] <= 'z');
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
