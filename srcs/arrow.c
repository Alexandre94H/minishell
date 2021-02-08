/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:50:30 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/08 16:33:38 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

int	init_std(int fd, bool in)
{
	int	ret;

	if (in)
		ret = dup2(fd, STDIN_FILENO);
	else
		ret = dup2(fd, STDOUT_FILENO);
	close(fd);
	return (ret);
}

int	arrow(char *prefix, char *file)
{
	int	fd;

	fd = -2;
	if (*prefix == '<' && prefix[1] != '<')
		fd = open(file, O_RDONLY);
	else if (*prefix == '>')
	{
		if (prefix[1] == '>' && prefix[2] != '>')
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (prefix[1] != '>')
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (fd < 0)
		return (fd);
	if (init_std(fd, *prefix == '<') == -1)
		return (-1);
	return (0);
}
