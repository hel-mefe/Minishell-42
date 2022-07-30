/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 09:04:38 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/30 17:39:20 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	ft_set(long *i, unsigned long long *nbr, long *n)
{
	*i = 0;
	*nbr = 0;
	*n = 1;
}

long long	ft_atoi(const char *str)
{
	long					i;
	unsigned long long		nbr;
	long					n;

	ft_set(&i, &nbr, &n);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		n = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * n);
}
