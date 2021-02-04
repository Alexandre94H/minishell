/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:46:10 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/04 16:31:45 by ahallain         ###   ########.fr       */
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

int	execute_file(char *folder, char *file, char **args, char **env)
{
	char	*temp;
	pid_t	pid;

	if (!(temp = malloc(sizeof(char *))))
		return (-1);
	*temp = 0;
	ft_stradd(&temp, folder);
	ft_stradd(&temp, "/");
	ft_stradd(&temp, file);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		execve(temp, args, env);
		exit(1);
	}
	free(temp);
	return (0);
}

int	execute(char **args, char **env)
{
	char			**folders;
	size_t			index;
	DIR				*dirp;
	struct dirent	*dp;
	int				ret;

	folders = ft_split(env_get(env, "PATH"), ':');
	ret = 256;
	index = 0;
	while (ret == 256 && folders[index])
	{
		dirp = opendir(folders[index]);
		while ((dp = readdir(dirp)))
			if (ft_equals(*args, dp->d_name))
			{
				ret = execute_file(folders[index], dp->d_name, args, env);
				break ;
			}
		closedir(dirp);
		index++;
	}
	free(folders);
	return (ret);
}
