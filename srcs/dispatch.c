/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/03 10:17:46 by ahallain         ###   ########.fr       */
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
