/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:19:05 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:34:10 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "default.h"
#include "../utils/lib.h"

void	update_content_apostrophe(char **content, size_t *index)
{
	ft_rmchar(content, *index);
	while ((*content)[*index] && (*content)[*index] != '\'')
		(*index)++;
	if ((*content)[*index])
		ft_rmchar(content, *index);
}

void	remove_backslash(char **content, size_t *index)
{
	ft_rmchar(content, *index);
	if ((*content)[*index])
		(*index)++;
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
			remove_backslash(content, &index);
		else if (!quote && (*content)[index] == '\'')
			update_content_apostrophe(content, &index);
		else if ((*content)[index] == '"')
		{
			quote = !quote;
			ft_rmchar(content, index);
		}
		else if ((*content)[index++] == '$'
			&& (ft_isalnum((*content)[index])
			|| (*content)[index] == '\'' || (*content)[index] == '"'
			|| (*content)[index] == '?' || (*content)[index] == '_'))
			env_loop(&index, content, env);
}
