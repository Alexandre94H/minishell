/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:27:34 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/04 12:17:42 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "../utils/lib.h"
#include "../utils/env.h"

bool			backslash_need(char c, bool quote)
{
	if (c == ' ')
		return (false);
	if (quote)
	{
		if (c == '\\'
			|| c == '"'
			|| c == '$')
			return (true);
	}
	else
		return (true);
	return (false);
}

char			*update_env_backslash(char *str, bool quote)
{
	size_t	index;
	size_t	index1;
	char	*value;

	index1 = 0;
	index = -1;
	while (str[++index])
		if (backslash_need(str[index], quote))
			index1++;
	if (!(value = malloc(sizeof(char *) * (index + index1 + 1))))
		return (NULL);
	value[index + index1] = 0;
	index1 = 0;
	index = -1;
	while (str[++index])
	{
		if (backslash_need(str[index], quote))
			value[index + index1++] = '\\';
		value[index + index1] = str[index];
	}
	return (value);
}

void			env_loop(size_t *index, char **str, char **env, bool quote)
{
	size_t	index1;
	char	*name;
	char	*value;

	if ((*str)[*index + 1] == '?')
	{
		value = ft_itoa(errno);
		ft_replace(str, *index, 2, value);
	}
	else
	{
		index1 = 1;
		while ((*str)[*index + index1]
			&& (ft_isalnum((*str)[*index + index1])
				|| (*str)[*index + index1] == '_'))
			index1++;
		name = ft_strndup(*str + *index + 1, index1 - 1);
		value = update_env_backslash(env_get(env, name), quote);
		free(name);
		ft_replace(str, *index, index1, value);
	}
	*index += ft_strlen(value, 0);
	free(value);
}

static	void	skip_quote(char **content, size_t *index)
{
	(*index)++;
	while ((*content)[*index] && (*content)[*index] != '\'')
		(*index)++;
	if (!(*content)[*index])
		(*index)--;
}

void			update_env(char **content, char **env)
{
	size_t	index;
	bool	quote;

	quote = false;
	index = -1;
	while ((*content)[++index])
		if (!index || (*content)[index - 1] != '\\')
		{
			if ((*content)[index] == '\'')
				skip_quote(content, &index);
			else if ((*content)[index] == '"')
				quote = !quote;
			else if ((*content)[index] == '$'
				&& (ft_isalnum((*content)[index + 1])
				|| (*content)[index + 1] == '?'
				|| (*content)[index + 1] == '_'))
			{
				env_loop(&index, content, env, quote);
				index--;
			}
		}
}
