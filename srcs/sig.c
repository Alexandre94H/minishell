/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:07:58 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/04 10:39:47 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include "../utils/lib.h"

void	call(int signum)
{
	ft_putstr("\b\b  \b\b");
	if (signum == SIGINT)
	{
		errno = 130;
		ft_putstr("\n$ ");
	}
}

void	sig()
{
	signal(SIGINT, call);
	signal(SIGQUIT, call);
}
