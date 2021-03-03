/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 10:23:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:31:58 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../utils/env.h"
#include "../utils/lib.h"

char	f_cd(char **args, char **env)
{
	char	*home;

	if (args[1] && args[2])
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	if (!args[1] || ft_equals(args[1], "--")
		|| ft_equals(args[1], "~"))
		home = env_get(env, "HOME");
	else if (ft_equals(args[1], "-"))
		home = env_get(env, "OLDPWD");
	else
		home = args[1];
	if (chdir(home) == -1)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		return (1);
	}
	if (!(home = getcwd(NULL, 0)))
		return (1);
	env_set(env, "OLDPWD", env_get(env, "PWD"));
	env_set(env, "PWD", home);
	free(home);
	return (0);
}
