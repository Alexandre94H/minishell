/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:10:31 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/27 19:18:02 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULT_H
# define DEFAULT_H

# include <stdbool.h>

void	sig();
void	sig_errno(void);
int		prompt(char **env);
char	dispatch(char *content, char **env);
int		arrow(char *prefix, char *file);
bool	update_arrow(char **content, char **env);
void	update_env(char **content, char **env);
void	update_content(char **content);
size_t	skip_quote(char *content);
char	**split_args(char **content, char **env);
int		execute(char **args, char **env);
int		call_function(char **args, char **env);
#endif
