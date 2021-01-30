/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 16:01:30 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 17:17:49 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/lib.h"
#include "functions/functions.h"

int	call_function(char **args, char **env)
{
	int			ret;
	static int	last_output;

	(void)env;
	ret = 256;
	if (ft_equals(*args, "exit"))
		ret = f_exit(args, last_output);
	return (ret);
}
