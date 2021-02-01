/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 09:42:00 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/01 18:49:51 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "default.h"
#include "../utils/lib.h"

int	main(int argc, char **argv, char **env)
{
	size_t	index;

	(void)argc;
	(void)argv;
	index = 0;
	while (env[index])
	{
		env[index] = ft_strndup(env[index], 0);
		index++;
	}
	return (prompt(env));
}
