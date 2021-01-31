/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:17:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/31 12:13:23 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

int	f_echo(char **args);
int	f_cd(char **args, char **env);
int	f_pwd(char **env);
int	f_export(char **args, char **env);
int	f_unset(char **args, char **env);
int	f_env(char **env);
int	f_exit(char **args, int last_output);
#endif
