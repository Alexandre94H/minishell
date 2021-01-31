/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:02:59 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 13:52:25 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/lib.h"
#include "../utils/env.h"

int	f_unset(char **args, char **env)
{
	if (!args[1])
	{
		ft_putstr("need something to unset\n");
		return (1);
	}
	env_rm(env, args[1]);
	return (0);
}