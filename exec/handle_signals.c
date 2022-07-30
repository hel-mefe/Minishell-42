/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:15:48 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/30 15:28:17 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	handel_sigint(int sig)
{
	if (sig == SIGINT && g_global.get_nb == 0)
	{
		g_global.get_nb_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGINT && g_global.get_nb == 1)
	{
		g_global.get_nb_status = 1;
		g_global.get_nb = -1;
		write(1, "\n", 1);
		close(0);
	}
}

void	handel_sigint1(int sig)
{
	(void)sig;
	g_global.get_nb_status = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "Quit\n", 5);
	g_global.get_nb_status = 131;
}

void	handle_signals(int i)
{
	if (i == 0)
	{
		signal(SIGINT, handel_sigint1);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 1)
	{
		signal(SIGINT, handel_sigint);
		signal(SIGQUIT, handle_sigquit);
	}
	if (i == 2)
	{
		signal(SIGINT, handel_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
}
