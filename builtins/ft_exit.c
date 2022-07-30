/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:54:02 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/30 17:59:32 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	exit_main(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

int	check_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	printexit(char **av, int i)
{
	char	*res;

	res = NULL;
	res = ft_strjoin(av[i], " :numeric argument required\n");
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd(res, 2);
	free(res);
	exit(255);
}

int	is_number_valid(char *av)
{
	unsigned long long	nbr;
	int					i;
	int					n;

	if (!av)
		return (1);
	n = 1;
	if (av[0] == '-')
		n = -1;
	i = 0;
	nbr = 0;
	while (av[i])
	{
		nbr = nbr * 10 + (av[i] - '0');
		if ((nbr > (unsigned long long) LLONG_MAX && n == 1) \
		|| (nbr > (unsigned long long) LLONG_MAX + 1 && n == -1))
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
	while (av[i] && av)
	{
		if (!check_exit(av[i]) || \
		(!ft_isalpha(av[i][0]) && !is_number_valid(av[i])))
			printexit(av, i);
		else if (av[i + 1] == 0)
		{
			g_global.get_nb_status = atoi(av[i]);
			exit(g_global.get_nb_status);
		}
		else
		{
			printf("exit \nMinishell : exit : too many arguments\n");
			g_global.get_nb_status = 1;
			return ;
		}
		i++;
	}	
}
