/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:07:58 by ahallain          #+#    #+#             */
/*   Updated: 2021/02/05 20:30:46 by ahallain         ###   ########.fr       */
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

void	sig(void)
{
	signal(SIGINT, call);
	signal(SIGQUIT, call);
}
