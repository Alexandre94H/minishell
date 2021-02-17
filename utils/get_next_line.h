/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 21:50:37 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/17 16:08:00 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <stddef.h>

bool	ft_includes(char *str, char c);
void	ft_addstr(char *from, char **to);
char	*ft_getstr(char *from, char c);
size_t	ft_strlen(char *str, char c);
void	ft_rmfirst(char **str, size_t len);
#endif
