/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:48:59 by marvin            #+#    #+#             */
/*   Updated: 2022/06/06 17:48:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void    ft_pwd(t_env **env_v)
{
    char buffer[1024];
    t_env *new;

    new = search_element(env_v, "PWD");
    if (getcwd(buffer, 1024))
    {
        printf("%s\n",buffer);
        get_nb_status = 0;
    }
    else if (getcwd(buffer, 1024) == NULL)
    {
        printf("%s\n", new->data);
        get_nb_status = 1;
    }
}