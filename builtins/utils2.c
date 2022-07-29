/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:19:56 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/30 00:22:39 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	init_spl(char **spl, char **av, int i, t_env **env_v)
{
	int	len;

	len = ft_strlen(av[i]);
	spl[1] = NULL;
	spl[0] = ft_substr(av[i], 0, (len - ft_strlen(spl[1])));
	if (!check_export(spl[0]))
	{
		print_err(av);
		free(spl[0]);
		return ;
	}
	check_evr(env_v, spl, av, 0);
	free(spl[0]);
}
