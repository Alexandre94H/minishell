/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:17:35 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/03 07:29:10 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

char	f_echo(char **args);
char	f_cd(char **args, char **env);
char	f_pwd(char **env);
char	f_export(char **args, char **env);
char	f_unset(char **args, char **env);
char	f_env(char **env);
char	f_exit(char **args);
#endif
