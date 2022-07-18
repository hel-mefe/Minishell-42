/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:21:47 by marvin            #+#    #+#             */
/*   Updated: 2022/06/06 15:21:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void    print_echo(char **s)
{
    int i;

    i = 0;
    while (s[i])
    {
        printf("%s", s[i]);
        if (s[i + 1])
            printf(" ");
        i++;
    }
}

int     check_new(char *str)
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

void    ft_echo(char **av)
{
    int i;
    int new_line;

    i = 1;
    new_line = 0;
    while(av[i] && av[i][0] == '-' && av[i][1] != '\0')
    {
        if (!check_new(av[i]))
            new_line = 1;
        else
            break ;
        i++;
    }
    print_echo(&av[i]);
    if(!new_line)
		printf("\n");
    get_nb_status = 0;
}
