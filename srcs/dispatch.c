/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/02 22:05:48 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "default.h"
#include "../utils/lib.h"
#include "../functions/functions.h"

int		run(char *content, char **env)
{
	char	**args;
	size_t	index;
	int		pid;
	int		status;

	args = split_args(content, env);
	if (ft_equals(*args, "exit"))
		return (f_exit(args) + 1);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		call_function(args, env);
		execute(args, env);
		index = 0;
		while (args[index])
			free(args[index++]);
		free(args);
		exit(1);
	} else {
		wait(&status);
		errno = WEXITSTATUS(status);
	}
	return (0);
}

int		dispatch(char *content, char **env)
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
		if (ret)
			errno = ret - 1;
		free(contents[index++]);
	}
	free(contents);
	if (ret)
		return (1);
	return (0);
}
