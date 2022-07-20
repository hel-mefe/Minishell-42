/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:48:59 by marvin            #+#    #+#             */
/*   Updated: 2022/07/19 21:36:17 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	ft_pwd(t_env **env_v)
{
	char	buffer[1024];
	t_env	*new;

	if (getcwd(buffer, 1024))
	{
		printf("%s\n", buffer);
		g_global.get_nb_status = 0;
	}
	else if (getcwd(buffer, 1024) == NULL)
	{
		new = search_element(env_v, "PWD");
		if (!new)
			return ;
		g_global.get_nb_status = 1;
	}
}
