/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_export_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:41:50 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:32:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

void		sort_env_loop(char ***sort)
{
	bool	edit;
	size_t	index;
	size_t	index1;
	char	*temp;

	edit = true;
	while (edit)
	{
		edit = false;
		index = -1;
		while ((*sort)[++index + 1])
		{
			index1 = 0;
			while ((*sort)[index][index1]
				&& (*sort)[index][index1] == (*sort)[index + 1][index1])
				index1++;
			if ((*sort)[index][index1] > (*sort)[index + 1][index1])
			{
				edit = true;
				temp = (*sort)[index];
				(*sort)[index] = (*sort)[index + 1];
				(*sort)[index + 1] = temp;
			}
		}
	}
}

char		**sort_env(char **env)
{
	char	**sort;
	size_t	index;

	index = 0;
	while (env[index])
		index++;
	if (!(sort = malloc(sizeof(char **) * (index + 1))))
		return (NULL);
	sort[index] = 0;
	while (index--)
		sort[index] = env[index];
	sort_env_loop(&sort);
	return (sort);
}
