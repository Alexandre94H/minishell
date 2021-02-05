/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/05 10:19:02 by ahallain         ###   ########.fr       */
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

	args = split_args(content, env);
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
	return (ret);
}

char	fork_run(char *content, char **new, bool last)
{
	pid_t	pid;
    int		pipefd[2];
	int		status;

	if (!last)
		if (pipe(pipefd) == -1)
			return (1);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (!last)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		exit(run(content, new));
	}
	if (!last)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	wait(&status);
	return (WEXITSTATUS(status));
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

	fork = ft_stristr(content, "|") == -1 ? false : true;
	pipes = ft_split(content, '|');
	ret = 0;
	index = 0;
	while (pipes[index])
	{
		contents = ft_split(pipes[index], ';');
		index1 = 0;
		while (!ret && contents[index1])
		{
			if (fork)
				ret = fork_run(contents[index1], env, !pipes[index + 1]);
			else
				ret = run(contents[index1], env);
			free(contents[index1++]);
		}
		free(contents);
		free(pipes[index++]);
	}
	free(pipes);
	if (ret < 0)
		return (1);
	if (fork)
		while (index--)
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	errno = ret;
	return (0);
}
