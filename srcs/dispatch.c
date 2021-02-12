/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/12 16:53:51 by ahallain         ###   ########.fr       */
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

char	run(char **content, char **env)
{
	char	**args;
	size_t	index;
	int		ret;

	args = split_args(content, env);
	if (!args || !*args)
	{
		if (!args)
			errno = 1;
		return (0);
	}
	ret = call_function(args, env);
	if (ret == 256)
		ret = execute(args, env);
	if (ret == 256)
	{
		ft_putstr_fd("command not found\n", 2);
		errno = 127;
	}
	else if (ret >= 0)
		errno = ret;
	index = 0;
	while (args[index])
		free(args[index++]);
	free(args);
	return (ret);
}

char	fork_run(char **content, char **new, bool last)
{
	pid_t	pid;
    int		pipefd[2];

	if (!last)
		if (pipe(pipefd) == -1)
			return (1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!last)
	{
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		else
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
	}
	if (pid == 0)
	{
		run(content, new);
		exit(errno);
	}
	return (errno);
}

char	dispatch(char *content, char **env)
{
	bool		fork;
	char		**pipes;
	char		**contents;
	size_t		index;
	size_t		index1;
	int			ret;
	int			status;

	contents = ft_split(content, ';');
	ret = 0;
	index = 0;
	while (contents[index])
	{
		pipes = ft_split(contents[index], '|');
		fork = pipes[0] && pipes[1] ? true : false;
		index1 = 0;
		while (!ret && pipes[index1])
		{
			if (fork)
				ret = fork_run(pipes + index1, env, !pipes[index1 + 1]);
			else
				ret = run(pipes + index1, env);
			free(pipes[index1++]);
		}
		free(pipes);
		free(contents[index++]);
	}
	free(contents);
	if (fork)
		while (waitpid(-1, &status, 0) == 0)
			errno = WEXITSTATUS(status);
	if (ret < 0)
		return (1);
	return (0);
}
