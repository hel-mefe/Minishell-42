/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:04:18 by marvin            #+#    #+#             */
/*   Updated: 2022/07/19 20:34:44 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	help_changelink(t_env **env_v, char *buffer, char *s, t_env *new)
{
	buffer = getcwd(s, 100);
	if (!buffer)
		return ;
	new = search_element(env_v, "PWD");
	if (!new)
		return ;
	remove_name(env_v, new->name);
	new = ft_lstnew(ft_strdup("PWD"), ft_strdup(buffer));
	ft_lstadd_back(env_v, new);
}

void	change_oldpwd(t_env **env_v, char *str, char *buffer, t_env *new)
{
	new = ft_lstnew(ft_strdup(str), ft_strdup(buffer));
	ft_lstadd_back(env_v, new);
}

void	change_link(t_env **env_v, int i)
{
	char	s[1024];
	char	*buffer;
	t_env	*new;

	buffer = NULL;
	new = NULL;
	if (i == 1)
	{
		new = search_element(env_v, "PWD");
		if (!new)
			return ;
		buffer = getcwd(s, 1024);
		if (!buffer)
			return ;
		new = search_element(env_v, "OLDPWD");
		if (!new)
		{
			change_oldpwd(env_v, "OLDPWD", buffer, new);
			return ;
		}
		remove_name(env_v, new->name);
		change_oldpwd(env_v, "OLDPWD", buffer, new);
	}
	else if (i == 2)
		help_changelink(env_v, buffer, s, new);
}

void	change_pwd(t_env **env_v, char **av, char *path, int i)
{
	change_link(env_v, 1);
	if (i == 0)
	{
		if (chdir(av[1]) != 0)
		{
			g_global.get_nb_status = 1;
			printf("cd : %s : %s\n", av[1], strerror(errno));
		}
	}
	else if (i == 1)
	{
		if (chdir(path) != 0)
			printf("cd : %s\n", strerror(errno));
	}
	change_link(env_v, 2);
}

void	ft_cd(t_env **env_v, char **av)
{
	char	*path;
	t_env	*new;

	path = NULL;
	if (!av[1] || (av[1][0] == '~' && av[1][1] == '\0'))
	{
		new = search_element(env_v, "HOME");
		if (!new)
			return ;
		change_pwd(env_v, av, new->data, 1);
		g_global.get_nb_status = 0;
	}
	else if (av[1])
	{
		g_global.get_nb_status = 0;
		change_pwd(env_v, av, path, 0);
	}
}
