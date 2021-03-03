/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 18:22:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:37:43 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "default.h"
#include "../utils/lib.h"

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
