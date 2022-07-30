/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:21:47 by marvin            #+#    #+#             */
/*   Updated: 2022/07/30 15:25:02 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	print_echo(char **s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putstr_fd(s[i], fd);
		if (s[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
}

int	check_new(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	handle_sign(t_env **env_v, t_env *new)
{
	new = search_element(env_v, "HOME");
	if (!new)
		return ;
	ft_putstr_fd(new->data, 1);
	ft_putstr_fd("\n", 1);
}

void	ft_echo(t_env **env_v, char **av, int fd)
{
	int		i;
	int		new_line;
	t_env	*new;

	i = 1;
	new_line = 0;
	new = NULL;
	if (!ft_strcmp(av[i], "~") && av[i + 1] == 0)
	{
		handle_sign(env_v, new);
		return ;
	}
	while (av && av[i] && av[i][0] == '-' && av[i][1] != '\0')
	{
		if (!check_new(av[i]))
			new_line = 1;
		else
			break ;
		i++;
	}
	print_echo(&av[i], fd);
	if (!new_line)
		ft_putstr_fd("\n", fd);
	g_global.get_nb_status = 0;
}
