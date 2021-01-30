/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 22:56:30 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "default.h"
#include "utils/lib.h"

int	dispatch(char *content, char **env)
{
	int			ret;
	char		**args;
	static int	last_output;

	args = ft_split(content, ' ');
	ret = call_function(args, env, last_output);
	if (ret > 255)
		ret = execute(args, env);
	free(args);
	if (ret > 255)
		ft_putstr("command not found\n");
	else if (ret < 0)
		return (-1 * (ret + 1));
	else
		last_output = ret;
	return (-1);
}
