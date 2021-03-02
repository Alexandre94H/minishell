/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 09:42:00 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/02 20:17:46 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"

int	main(int argc, char **argv, char **env)
{
	size_t	index;
	int		ret;

	(void)argc;
	(void)argv;
	index = 0;
	while (env[index])
	{
		env[index] = ft_strndup(env[index], -1);
		index++;
	}
	ret = prompt(env);
	index = 0;
	while (env[index])
		free(env[index++]);
	return (ret);
}
