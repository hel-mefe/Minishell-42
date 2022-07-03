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

void    ft_echo(char **av)
{
    int i;
    int j;
    int echo_e;

    i = 1;
    echo_e = 0;
    j = 0;
    while(av[i][0] == '-'  &&  av[i][1] == 'n')
    {
        j = 1;
        while (av[i][j] == 'n')
        {
            echo_e = 1;
            j++;
        }
        i++;
    }
    while (av[i])
    {
        printf("%s", av[i]);
        if (av[i] && av[i + 1])
                printf(" ");
        i++;
    }
    if (echo_e == 0)
        printf("\n");
	get_nb_status = 0;
}
