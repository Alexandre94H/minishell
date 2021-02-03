/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 11:35:39 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/03 07:29:03 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/lib.h"
#include "../utils/env.h"

char	f_pwd(char **env)
{
	ft_putstr(env_get(env, "PWD"));
	ft_putchar('\n');
	return (0);
}
