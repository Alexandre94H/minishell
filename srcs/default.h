/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:10:31 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 18:59:11 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULT_H
# define DEFAULT_H

# include <stdbool.h>

void	sig();
void	sig_errno(void);
size_t	skip_quote(char *content);
bool	right_syntax(char *content);
int		prompt(char **env);
int		arrow(char *prefix, char *file);
bool	update_arrow(char **content, char **env);
void	update_env(char **content, char **env);
void	update_content(char **content);
char	**split_args(char **content, char **env);
int		execute(char **args, char **env);
int		call_function(char **args, char **env);
char	run(char **content, char **env);
char	fork_run(char **content, char **new, bool last);
char	dispatch(char *content, char **env);
#endif
