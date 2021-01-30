/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 10:10:31 by ahallain          #+#    #+#             */
/*   Updated: 2021/01/30 16:18:38 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULT_H
# define DEFAULT_H

int	prompt(char **env);
int	dispatch(char *content, char **env);
int	execute(char **args, char **env);
int	call_function(char **args, char **env);
#endif
