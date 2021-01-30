/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 11:07:44 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/lib.h"
#include "functions/functions.h"

int	dispatch(char *content, char **env)
{
	int			ret;
	char		**args;
	static int	last_output;

	(void)env;
	ret = -1;
	args = ft_split(content, ' ');
	if (!*args)
		return (ret);
	if (!ft_strncmp(*args, "exit", 256))
		return (f_exit(args, last_output));
	return (ret);
}
