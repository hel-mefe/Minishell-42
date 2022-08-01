/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:54:41 by marvin            #+#    #+#             */
/*   Updated: 2022/07/30 14:46:20 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	init_env(t_env **env_v, char **env)
{
	t_env	*new;
	char	**spl;
	int		i;

	new = NULL;
	i = 0;
	while (env[i])
	{
		if (strstr(env[i], "="))
		{
			spl = ft_split(env[i], '=');
			new = ft_lstnew(spl[0], spl[1]);
			free(spl);
		}
		else
			new->name = env[i];
		if (env_v != NULL && new != NULL)
			ft_lstadd_back(env_v, new);
		i++;
	}
}

void	print_errr(t_env **env_v, char **av)
{
	char	*res;

	g_global.get_nb_status = 127;
	if (search_element(env_v, "PATH"))
	{
		res = ft_strjoin(av[1], " : No such file or directory\n");
		ft_putstr_fd(res, 2);
		free(res);
	}
	else
	{
		res = ft_strjoin("env", " : No such file or directory\n");
		ft_putstr_fd(res, 2);
		free(res);
	}
}

void	ft_env(t_env **env_v, char **av, int fd)
{
	t_env	*env;

	env = *env_v;
	if (!av[1] && search_element(env_v, "PATH"))
	{
		while (env)
		{
			if (env->data != NULL)
			{
				ft_putstr_fd(env->name, fd);
				ft_putstr_fd(env->data, fd);
				ft_putstr_fd("\n", fd);
			}
			env = env->next;
		}
	}
	else
		print_errr(env_v, av);
}
