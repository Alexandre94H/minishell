/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:07:43 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 10:57:02 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils/lib.h"
#include "get_next_line/get_next_line.h"
#include "default.h"

int	prompt(char **env)
{
	int		ret;
	char	*line;

	ret = -1;
	while (ret == -1)
	{
		ft_putstr("$ ");
		get_next_line(2, &line);
		ret = dispatch(line, env);
		free(line);
	}
	return (ret);
}
