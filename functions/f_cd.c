/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 10:23:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/07 12:24:03 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../utils/env.h"
#include "../utils/lib.h"

char	f_cd(char **args, char **env)
{
	char	*home;

	if (!args[1] || ft_equals(args[1], "--"))
		home = env_get(env, "HOME");
	else if (ft_equals(args[1], "-"))
		home = env_get(env, "OLDPWD");
	else
		home = args[1];
	if (chdir(home) == -1)
		return (1);
	if (!(home = getcwd(NULL, 0)))
		return (1);
	env_set(env, "OLDPWD", env_get(env, "PWD"));
	env_set(env, "PWD", home);
	return (0);
}
