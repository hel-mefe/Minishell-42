/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:54:02 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/25 18:23:27 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	ft_exit(char **av)
{
	int	i;

	i = 1;
	if (av[i] == '\0')
		exit(g_global.get_nb_status);
	else if (av[i] && av[i + 1] == 0)
	{
		g_global.get_nb_status = atoi(av[i]);
		exit(g_global.get_nb_status);
	}
	else
		printf("exit \nMinishell : exit : too many arguments\n");
}
