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

void	check_err(void)
{
	ft_putstr_fd(strerror(errno), 2);
	return ;
}

void	remove_name(t_env **env_v, char *name)
{
	t_env	*new;
	t_env	*prev;
	t_env	*current_node;

	if ((*env_v)->name == name)
	{
		new = *env_v;
		*env_v = (*env_v)->next;
		free(new);
	}
	else
	{
		prev = *env_v;
		current_node = (*env_v)->next;
		while (current_node != NULL && ft_strcmp(current_node->name, name))
		{
			prev = prev->next;
			current_node = current_node->next;
		}
		prev->next = current_node->next;
		free(current_node);
	}
}

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

void	change_pwd(t_env **env_v, char **av, char *path, int i)
{
	char	s[1024];
	char	*buffer;
	char	*res;
	t_env	*new;
	
	
	new = search_element(env_v, "PWD");
	buffer = getcwd(s, 1024);
	if (!buffer)
		buffer = new->data;
	new = search_element(env_v, "OLDPWD");
	remove_name(env_v, new->name);
	new = ft_lstnew("OLDPWD", strdup(buffer));
	ft_lstadd_back(env_v, new);
	if(i == 0)
	{
		if (chdir(av[1]) != 0)
		{
			get_nb_status = 1;
			printf("cd : %s : %s\n", av[1], strerror(errno));
		}
	}
	else if (i == 1)
	{
		if (chdir(path) != 0)
			printf("cd : %s\n", strerror(errno));
	}
	buffer = getcwd(s, 100);
	if (!buffer)
		return ;
	new = search_element(env_v, "PWD");
	remove_name(env_v, new->name);
	new = ft_lstnew("PWD", strdup(buffer));
	ft_lstadd_back(env_v, new);
}

char	*get_path(t_env **env_v)
{
	t_env *new;

	new = search_element(env_v, "HOME");
	return (new->data);
}

void    ft_cd(t_env **env_v, char **av)
{
	char	*path;

	path = NULL;
	if (!av[1])
	{
		path = get_path(env_v);
		change_pwd(env_v, av, path, 1);
	}
	else
		change_pwd(env_v, av, path, 0);
}
