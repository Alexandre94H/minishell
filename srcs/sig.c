/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:07:58 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/06 12:44:10 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include "../utils/lib.h"

void	call(int signum)
{
	ft_putstr_fd("\b\b  \b\b", 1);
	if (signum == SIGINT)
	{
		errno = 130;
		ft_putstr_fd("\n$ ", 1);
	}
}

void	sig(void)
{
	signal(SIGINT, call);
	signal(SIGQUIT, call);
}
