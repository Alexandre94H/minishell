/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/04 09:58:46 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include "default.h"
#include "../utils/lib.h"
#include "../functions/functions.h"

char	run(char *content, char **env)
{
	char	**args;
	size_t	index;
	int		ret;
	int		fd;

	args = split_args(content, env);
	int file_desc = open("STDOUT_FILENO.log", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    fd = dup(STDOUT_FILENO);
	dup2(file_desc, STDOUT_FILENO);
	close(file_desc);
	ret = call_function(args, env);
	if (ret == 256)
		ret = execute(args, env);
	if (ret == 256)
	{
		ft_putstr("command not found\n");
		errno = 1;
	}
	else if (ret >= 0)
		errno = ret;
	index = 0;
	while (args[index])
		free(args[index++]);
	free(args);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (ret);
}

char	dispatch(char *content, char **env)
{
	char		**contents;
	size_t		index;
	int			ret;

	contents = ft_split(content, ';');
	index = 0;
	ret = 0;
	while (!ret && contents[index])
	{
		ret = run(contents[index], env);
		free(contents[index++]);
	}
	free(contents);
	if (ret > 0)
		errno = ret;
	else if (ret < 0)
		return (1);
	return (0);
}
