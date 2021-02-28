/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:02:59 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/28 19:55:31 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utils/lib.h"
#include "../utils/env.h"

bool	unset_loop(char *arg, char **env)
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
	temp = ft_strndup(arg, ft_strlen(arg, '='));
	if (right)
		env_rm(env, temp);
	else
	{
		ft_putchar_fd('`', 1);
		ft_putstr_fd(temp, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
	}
	free(temp);
	return (right);
}

char	f_unset(char **args, char **env)
{
	size_t	index;
	char	ret;

	ret = 0;
	index = 1;
	while (args[index])
	{
		if (!unset_loop(args[index], env))
			ret = 1;
		index++;
	}
	return (ret);
}
