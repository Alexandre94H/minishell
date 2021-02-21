/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:10:31 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/21 10:52:20 by ahallain         ###   ########.fr       */
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
int		arrow(char *prefix, char *file);
void	update_str(char **str, char **env, bool force_slash);
#endif
