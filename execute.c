/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:46:10 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 22:42:17 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "utils/lib.h"
#include "utils/env.h"
#include <stdio.h>

int	execute_file(char *folder, char *file, char **args, char **env)
{
	char	*temp;
	pid_t	pid;
	int		status;

	if (!(temp = malloc(sizeof(char *))))
		return (-1);
	temp[0] = 0;
	ft_stradd(&temp, folder);
	ft_stradd(&temp, "/");
	ft_stradd(&temp, file);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
		execve(temp, args, env);
	else
		waitpid(pid, &status, WSTOPPED);
	free(temp);
	return (WEXITSTATUS(status));
}

int	execute(char **args, char **env)
{
	char			**folders;
	size_t			index;
	int				ret;
	DIR				*dirp;
	struct dirent	*dp;

	folders = ft_split(env_get(env, "PATH"), ':');
	ret = 256;
	index = 0;
	while (ret == 256 && folders[index])
	{
		dirp = opendir(folders[index]);
		while ((dp = readdir(dirp)))
			if (ft_equals(*args, dp->d_name))
				ret = execute_file(folders[index], dp->d_name, args, env);
		closedir(dirp);
		index++;
	}
	free(folders);
	return (ret);
}
