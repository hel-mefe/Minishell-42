/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:04:18 by marvin            #+#    #+#             */
/*   Updated: 2022/06/26 19:41:04 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_env	*search_element(t_env **env_v, char *name)
{
	t_env *tmp;
	t_env *current;

	tmp = *env_v; 
	while(tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void    ft_cd(t_env **env_v, char **av)
{
	char	s[100];
	char	*buffer;
	t_env	*new;

	buffer = getcwd(s, 100);
	new = search_element(env_v, "OLDPWD");
	ft_unset(env_v, new->name);
	new = ft_lstnew("OLDPWD", strdup(buffer));
	ft_lstadd_back(env_v, new);
	chdir(av[1]);
	buffer = getcwd(s, 100);
	new = search_element(env_v, "PWD");
	ft_unset(env_v, new->name);
	new = ft_lstnew("PWD", strdup(buffer));
	ft_lstadd_back(env_v, new);
}
