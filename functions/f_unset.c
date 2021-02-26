/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:02:59 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/26 19:04:08 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../utils/lib.h"
#include "../utils/env.h"

char	f_unset(char **args, char **env)
{
	size_t	index;
	size_t	index1;
	bool	right;
	char	*temp;

	index = 1;
	while (args[index])
	{
		index1 = 0;
		right = ft_isalnum(args[index][index1]);
		while (args[index][index1] && ft_isalnum(args[index][index1]))
			index1++;
		if (args[index][index1] && args[index][index1] != '=')
			right = false;
		index1 = ft_strlen(args[index], '=');
		temp = ft_strndup(args[index], index1);
		if (right)
			env_rm(env, temp);
		else
		{
			ft_putchar_fd('`', 1);
			ft_putstr_fd(temp, 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
		}
		free(temp);
		index++;
	}
	env_rm(env, args[1]);
	return (0);
}
