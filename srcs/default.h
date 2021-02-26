/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:10:31 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/26 16:54:55 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULT_H
# define DEFAULT_H

# include <stdbool.h>

int		prompt(char **env);
char	dispatch(char *content, char **env);
int		execute(char **args, char **env);
int		call_function(char **args, char **env);
char	**split_args(char **content, char **env);
void	sig();
void	sig_errno(void);
int		arrow(char *prefix, char *file);
void	update_str(char **str, char **env, char c);
size_t	skip_quote(char *content);
#endif
