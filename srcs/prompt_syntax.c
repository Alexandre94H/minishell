/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:41:46 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/01 21:44:02 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include "default.h"
#include "../utils/lib.h"

bool	right_syntax_loop_arrow(char *content, size_t *index, bool *ret)
{
	(*index)++;
	if (content[*index - 1] == '>' && content[*index] == '>')
		(*index)++;
	while (content[*index] && ft_isspace(content[*index]))
		(*index)++;
	if (!content[*index]
		|| content[*index] == ';'
		|| content[*index] == '|'
		|| content[*index] == '<'
		|| content[*index] == '>')
	{
		*ret = false;
		return (false);
	}
	(*index)--;
	return (true);
}

bool	right_syntax_loop(char *content, size_t *index, bool *ret)
{
	if (content[*index] == '\''
		|| content[*index] == '"')
		*index += skip_quote(content + *index) - 1;
	else if (content[*index] == ';'
		|| content[*index] == '|')
		if (*ret)
			*ret = false;
		else
			return (false);
	else if (content[*index] == '<'
		|| content[*index] == '>')
	{
		if (!right_syntax_loop_arrow(content, index, ret))
			return (false);
	}
	else if (!ft_isspace(content[*index]))
		*ret = true;
	return (true);
}

bool	right_syntax(char *content)
{
	bool		ret;
	size_t		index;

	ret = false;
	index = 0;
	while (content[index])
	{
		if (!right_syntax_loop(content, &index, &ret))
			break ;
		if (content[index])
			index++;
	}
	if (!content[index])
		ret = true;
	if (!ret)
	{
		ft_putstr_fd("syntax error\n", 2);
		errno = 2;
	}
	return (ret);
}
