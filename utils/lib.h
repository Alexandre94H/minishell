/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:03:54 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/07 20:36:56 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <stddef.h>
# include <stdbool.h>

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strndup(const char *s1, long long len);
char	**ft_cut(char *str, char c);
size_t	ft_strlen(char *src, int c);
bool	ft_equals(char *str1, char *str2);
char	*ft_stradd(char **dst, char *str);
int		ft_stristr(char *str, char *value);
void	ft_replace(char **str, char *from, char *to);
int		ft_isalnum(int c);
char	*ft_itoa(int n);
void	ft_rmchar(char **str, size_t index);
#endif
