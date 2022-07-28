/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:54:02 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/28 15:39:50 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

int	check_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **av)
{
	int	i;

	i = 1;
	if (av[i] == '\0')
		exit(g_global.get_nb_status);
	else if (av[i] && av[i + 1] == 0)
	{
		if (check_exit(av[i]))
		{
			printf("exit\n");
			printf("Minishell : exit :%s :numeric argument required ", av[i]);
			exit(255);
		}
		else
		{
			g_global.get_nb_status = atoi(av[i]);
			exit(g_global.get_nb_status);
		}
	}
	else
	{
		printf("exit \nMinishell : exit : too many arguments\n");
		g_global.get_nb_status = 1;
	}
}
