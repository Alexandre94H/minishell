/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/01 13:50:56 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"
#include "../utils/get_next_line.h"

int	prompt(char **env)
{
	int		ret;
	char	*line;

	ret = -1;
	while (ret == -1)
	{
		ft_putstr("\e[33m");
		ft_putstr(env_get(env, "LOGNAME"));
		ft_putstr("\e[0m in \e[35m");
		ft_putstr(env_get(env, "PWD"));
		ft_putstr("\e[0m\n$ ");
		get_next_line(2, &line);
		if (*line)
			ret = dispatch(line, env);
		free(line);
		ft_putchar('\n');
	}
	return (ret);
}
