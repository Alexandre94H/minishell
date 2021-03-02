/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:45:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/02 19:17:13 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include "default.h"
#include "../utils/lib.h"
#include "../utils/env.h"

size_t	skip_quote(char *content)
{
	size_t	index;

	index = 1;
	while (content[index])
	{
		if (content[index] == *content
			&& (content[index] == '\'' || content[index - 1] != '\\'))
			break ;
		index++;
	}
	return (index + !!content[index]);
}

void	update_content_apostrophe(char **content, size_t *index)
{
	ft_rmchar(content, *index);
	while ((*content)[*index] && (*content)[*index] != '\'')
		(*index)++;
	if ((*content)[*index])
		ft_rmchar(content, *index);
}

void	update_content(char **content, char **env)
{
	size_t	index;
	bool	quote;

	quote = false;
	index = 0;
	while ((*content)[index])
		if ((*content)[index] == '\\'
			&& (!quote
			|| (*content)[index + 1] == '"'
			|| (*content)[index + 1] == '$'
			|| (*content)[index + 1] == '\\'))
			ft_rmchar(content, index++);
		else if (!quote && (*content)[index] == '\'')
			update_content_apostrophe(content, &index);
		else if ((*content)[index] == '"')
		{
			quote = !quote;
			ft_rmchar(content, index);
		}
		else if ((*content)[index++] == '$'
			&& (ft_isalnum((*content)[index])
			|| (*content)[index] == '\''
			|| (*content)[index] == '\"'))
			env_loop(&index, content, env);
}

size_t	add_arg(char ***args, char *content, char **env)
{
	size_t	index;
	size_t	index1;
	char	*arg;

	index = 0;
	while (content[index] && ft_isspace(content[index]))
		index++;
	index1 = 0;
	while (content[index + index1]
		&& (index + index1 == 0
		|| content[index + index1 - 1] == '\\'
		|| !ft_isspace(content[index + index1])))
		if (content[index + index1] == '\'' || content[index + index1] == '"')
			index1 += skip_quote(content + index + index1);
		else
			index1++;
	if (!index1)
		return (index);
	arg = ft_strndup(content + index, index1);
	update_content(&arg, env);
	ft_addtab((void ***)args, arg);
	return (index + index1);
}

char	**split_args(char **content, char **env)
{
	char	**args;
	size_t	index;

	if (!update_arrow(content, env))
		return (NULL);
	if (!(args = malloc(sizeof(char **))))
		return (NULL);
	*args = 0;
	index = 0;
	while ((*content)[index])
		index += add_arg(&args, (*content) + index, env);
	return (args);
}
