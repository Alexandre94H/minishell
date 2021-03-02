/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:46:10 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/02 16:53:18 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"

int	launch(char *file, char **args, char **env)
{
	pid_t	pid;
	int		status;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (256);
	close(fd);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		execve(file, args, env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (!WIFSIGNALED(status))
		errno = WEXITSTATUS(status);
	return (errno);
}

int	execute_file(char *folder, char *file, char **args, char **env)
{
	char	*temp;
	int		ret;

	if (!(temp = malloc(sizeof(char *))))
		return (-1);
	*temp = 0;
	ft_addstr(folder, &temp);
	ft_addstr("/", &temp);
	ft_addstr(file, &temp);
	ret = launch(temp, args, env);
	free(temp);
	return (ret);
}

int	execute(char **args, char **env)
{
	char			**folders;
	size_t			index;
	int				ret;

	if (!**args || ft_equals(*args, ".") || ft_equals(*args, ".."))
		return (256);
	if (**args == '/')
		return (launch(*args, args, env));
	folders = ft_split(env_get(env, "PATH"), ':');
	ret = 256;
	index = 0;
	while (ret == 256 && folders[index])
	{
		ret = execute_file(folders[index], *args, args, env);
		if (ret != 256)
			break ;
		index++;
	}
	index = 0;
	while (folders[index])
		free(folders[index++]);
	free(folders);
	return (ret);
}
