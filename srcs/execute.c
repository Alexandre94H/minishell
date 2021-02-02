/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:46:10 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/02 20:38:41 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "../utils/lib.h"
#include "../utils/env.h"

void	execute_file(char *folder, char *file, char **args, char **env)
{
	char	*temp;

	if (!(temp = malloc(sizeof(char *))))
		return ;
	*temp = 0;
	ft_stradd(&temp, folder);
	ft_stradd(&temp, "/");
	ft_stradd(&temp, file);
	execve(temp, args, env);
	free(temp);
	exit(errno);
}

void	execute(char **args, char **env)
{
	char			**folders;
	size_t			index;
	DIR				*dirp;
	struct dirent	*dp;

	folders = ft_split(env_get(env, "PATH"), ':');
	index = 0;
	while (folders[index])
	{
		dirp = opendir(folders[index]);
		while ((dp = readdir(dirp)))
			if (ft_equals(*args, dp->d_name))
				execute_file(folders[index], dp->d_name, args, env);
		closedir(dirp);
		index++;
	}
	free(folders);
}
