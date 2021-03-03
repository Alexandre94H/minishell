/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:01:30 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:35:33 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/lib.h"
#include "../functions/functions.h"

int	call_function(char **args, char **env)
{
	int	ret;

	ret = 256;
	if (ft_equals(*args, "echo"))
		ret = f_echo(args);
	else if (ft_equals(*args, "cd"))
		ret = f_cd(args, env);
	else if (ft_equals(*args, "pwd"))
		ret = f_pwd(env);
	else if (ft_equals(*args, "export"))
		ret = f_export(args, env);
	else if (ft_equals(*args, "unset"))
		ret = f_unset(args, env);
	else if (ft_equals(*args, "env"))
		ret = f_env(env);
	else if (ft_equals(*args, "exit"))
		ret = f_exit(args);
	return (ret);
}
