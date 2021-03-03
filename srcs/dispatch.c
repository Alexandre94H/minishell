/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:18:13 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:35:52 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "default.h"
#include "../utils/lib.h"

bool	contains_nospace(char *str, size_t max)
{
	size_t	index;

	index = 0;
	while (str[index] && index < max)
		if (!ft_isspace(str[index++]))
			return (true);
	return (false);
}

char	**split_smouth(char *str, char c)
{
	size_t	index;
	char	**tab;

	if (!(tab = malloc(sizeof(char **))))
		return (NULL);
	*tab = 0;
	index = -1;
	while (str[++index])
		if (str[index] == '\'' || str[index] == '"')
		{
			index += skip_quote(str + index) - 1;
			if (!str[index])
				index--;
		}
		else if (str[index] == c && (!index || str[index - 1] != '\\'))
		{
			ft_addtab((void ***)&tab, ft_strndup(str, index));
			str += index + 1;
			index = -1;
		}
	if (!*tab || contains_nospace(str, index))
		ft_addtab((void ***)&tab, ft_strndup(str, index));
	return (tab);
}

char	dispatch(char *content, char **env)
{
	char		**pipes;
	char		**contents;
	size_t		index;
	int			ret;

	contents = split_smouth(content, ';');
	ret = 0;
	index = 0;
	while (contents[index])
	{
		pipes = split_smouth(contents[index], '|');
		if (pipes[0] && pipes[1])
			ret = fork_run(pipes, env, false);
		else
		{
			sig_errno();
			ret = run(pipes, env);
		}
		ft_freetab((void ***)&pipes);
		free(contents[index++]);
	}
	free(contents);
	return (ret);
}
