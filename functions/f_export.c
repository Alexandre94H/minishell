/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:39:24 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/25 21:15:28 by ahallain         ###   ########.fr       */
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
			while (sort[index][index1] && sort[index][index1] == sort[index + 1][index1])
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
	index = 0;
	while (sort[index]) {
		index1 = ft_strlen(sort[index], '=') + 1;
		temp = ft_strndup(sort[index], index1);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(temp, 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(sort[index] + index1, 1);
		ft_putstr_fd("\"\n", 1);
		free(temp);
		index++;
	}
	free(sort);
}

char		f_export(char **args, char **env)
{
	if (!args[1])
		print_env(env);
	return (0);
}
