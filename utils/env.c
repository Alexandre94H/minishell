/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:03:49 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 16:54:19 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "lib.h"

char	*env_get(char **env, char *name)
{
	char	*temp;
	bool	equal;

	while (*env)
	{
		temp = ft_strndup(*env, ft_strlen(*env, '='));
		equal = ft_equals(temp, name);
		free(temp);
		if (equal)
			return (*env + ft_strlen(*env, '=') + 1);
		env++;
	}
	return ("");
}
