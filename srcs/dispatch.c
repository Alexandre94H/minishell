/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/26 16:54:58 by ahallain         ###   ########.fr       */
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
	int		ret;

	ret = 0;
	args = split_args(content, env);
	if (args && *args && **args)
	{
		ret = call_function(args, env);
		if (ret == 256)
			ret = execute(args, env);
		if (ret == 256)
		{
			ft_putstr_fd(*args, 2);
			ft_putstr_fd(": command not found\n", 2);
			errno = 127;
		}
		else if (ret >= 0)
			errno = ret;
	}
	else if (!args)
		errno = 1;
	if (args)
		ft_freetab((void ***)&args);
	return (ret < 0);
}

char	fork_run(char **content, char **new, bool last)
{
	pid_t	pid;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) || (pid = fork()) < 0)
		return (-1);
	if (!last)
	{
		close(pipefd[!!pid]);
		dup2(pipefd[!pid], !pid);
		close(pipefd[!pid]);
	}
	if (pid == 0)
	{
		sig_errno();
		run(content, new);
		exit(errno);
	}
	if (content[1] && fork_run(content + 1, new, !content[2]) < 0)
		return (-1);
	waitpid(pid, &status, 0);
	if (last)
		errno = WEXITSTATUS(status);
	return (0);
}

char	**split_smouth(char *str, char c)
{
	size_t	index;
	char	**tab;

	if (!(tab = malloc(sizeof(char **))))
		return (NULL);
	*tab = 0;
	index = -1;
	while (str[++index])
		if (str[index] == '\'' || str[index] == '"')
			index += skip_quote(str + index) - 1;
		else if (str[index] == c && (!index || str[index - 1] != '\\'))
		{
			ft_addtab((void ***)&tab, ft_strndup(str, index));
			str += index + 1;
			index = -1;
		}
	if (!*tab || (index && !ft_isspace(str[index - 1])))
		ft_addtab((void ***)&tab, ft_strndup(str, index));
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
		}
		ft_freetab((void ***)&pipes);
		free(contents[index++]);
	}
	free(contents);
	return (ret);
}
