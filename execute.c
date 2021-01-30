/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:46:10 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 17:17:03 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <dirent.h>
#include <unistd.h>
#include "utils/lib.h"
#include "utils/env.h"

int	execute(char **args, char **env)
{
	char			**folders;
	size_t			index;
	int				ret;
	DIR				*dirp;
	struct dirent	*dp;

	(void)args;
	folders = ft_split(env_get(env, "PATH"), ':');
	ret = 256;
	index = 0;
	while (folders[index])
	{
		dirp = opendir(folders[index++]);
		dp = readdir(dirp);
		closedir(dirp);
	}
	return (ret);
}
