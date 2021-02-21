/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/21 09:20:36 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
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

	ret = 0;
	args = split_args(content, env);
	if (args)
	{
		ret = call_function(args, env);
		if (ret == 256)
			ret = execute(args, env);
		if (ret == 256)
			ft_putstr_fd("command not found\n", 2);
		if (ret == 256)
			errno = 127;
		else if (ret >= 0)
			errno = ret;
	}
	else if (!args)
		errno = 1;
	index = 0;
	while (args[index])
		free(args[index++]);
	free(args);
	return (ret < 0);
}

char	fork_run(char **content, char **new, bool last)
{
	pid_t	pid;
	int		pipefd[2];
	int		status;

	if (!last)
		if (pipe(pipefd) == -1)
			return (-1);
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
	free(*content);
	if (content[1] && fork_run(content + 1, new, !content[2]) < 0)
		return (-1);
	if (last)
	{
		waitpid(pid, &status, 0);
		errno = WEXITSTATUS(status);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

char	**split_smouth(char *str, char c)
{
	size_t	index;
	size_t	index1;
	char	**tab;

	if (!(tab = malloc(sizeof(char **))))
		return (NULL);
	*tab = 0;
	index = -1;
	while (str[++index])
		if (str[index] == '\'' || str[index] == '"')
		{
			index1 = 1;
			while (str[index + index1] && str[index + index1] != str[index])
				index1++;
			index += index1;
		}
		else if (str[index] == c && (!index || str[index - 1] != '\\'))
		{
			ft_addtab(&tab, ft_strndup(str, index));
			str += index + 1;
			index = -1;
		}
	if (!*tab || (index && str[index - 1] != ' '))
		ft_addtab(&tab, ft_strndup(str, index));
	return (tab);
}

char	dispatch(char *content, char **env)
{
	char		**pipes;
	char		**contents;
	size_t		index;
	size_t		index1;
	int			ret;

	contents = split_smouth(content, ';');
	ret = 0;
	index = 0;
	while (contents[index])
	{
		pipes = split_smouth(contents[index], '|');
		if (pipes[0] && pipes[1])
			ret = fork_run(pipes, env, false);
		else
		{
			index1 = 0;
			while (!ret && pipes[index1])
				ret = run(pipes + index1++, env);
			index1 = 0;
			while (pipes[index1])
				free(pipes[index1++]);
		}
		free(pipes);
		free(contents[index++]);
	}
	free(contents);
	return (ret);
}
