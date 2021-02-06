/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:35:39 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/06 11:54:07 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/lib.h"
#include "../utils/env.h"

char	f_pwd(char **env)
{
	ft_putstr_fd(env_get(env, "PWD"), 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
