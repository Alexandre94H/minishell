/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 12:06:00 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils/lib.h"
#include "utils/env.h"
#include "get_next_line/get_next_line.h"
#include "default.h"

int	prompt(char **env)
{
	int		ret;
	char	*line;

	ret = -1;
	while (ret == -1)
	{
		ft_putstr(env_get(env, "PWD"));
		ft_putstr("$ ");
		get_next_line(2, &line);
		ret = dispatch(line, env);
		free(line);
	}
	return (ret);
}
