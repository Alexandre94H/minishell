/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:03:49 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 12:35:36 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lib.h"

char	*env_get(char **env, char *name)
{
	char	**cut;
	char	*ret;

	while (*env)
	{
		cut = ft_cut(*env++, '=');
		if (ft_equals(cut[0], name))
		{
			free(cut[0]);
			ret = cut[1];
			return (ret);
		}
	}
	return ("");
}
