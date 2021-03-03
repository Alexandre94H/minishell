/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 21:07:58 by ahallain          #+#    #+#             */
/*   Updated: 2021/03/03 16:13:27 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include "../utils/lib.h"

void	call(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n$ ", 1);
		errno = 130;
	}
	else
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		errno = 131;
	}
}

void	sig(void)
{
	signal(SIGINT, call);
	signal(SIGQUIT, call);
}

void	call_errno(int signum)
{
	if (signum == SIGINT)
		errno = 130;
	else
		errno = 131;
}

void	sig_errno(void)
{
	signal(SIGINT, call_errno);
	signal(SIGQUIT, call_errno);
}
