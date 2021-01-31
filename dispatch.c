/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 20:05:33 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "default.h"
#include "utils/lib.h"

int	run(char *content, char **env, int last_output)
{
	char	**args;
	size_t	index;
	int		ret;

	args = ft_split(content, ' ');
	ret = call_function(args, env, last_output);
	if (ret > 255)
		ret = execute(args, env);
	index = 0;
	while (args[index])
		free(args[index++]);
	free(args);
	return (ret);
}

int	dispatch(char *content, char **env)
{
	char		**contents;
	size_t		index;
	int			ret;
	static int	last_output;

	contents = ft_split(content, ';');
	index = 0;
	while (contents[index])
	{
		ret = run(contents[index], env, last_output);
		free(contents[index++]);
		if (ret < 0)
			break ;
	}
	free(contents);
	if (ret > 255)
		ft_putstr("command not found\n");
	else if (ret < 0)
		return (-1 * (ret + 1));
	else
		last_output = ret;
	return (-1);
}
