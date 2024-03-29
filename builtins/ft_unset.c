/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:21:23 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/30 15:06:43 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

int	check_unset(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isalpha(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	help_unset(t_env **env_v, char **name, int i)
{
	t_env	*current_node;
	t_env	*prev;

	prev = *env_v;
	current_node = NULL;
	current_node = (*env_v)->next;
	while (current_node != NULL && ft_strcmp(current_node->name, name[i]))
	{
		prev = prev->next;
		current_node = current_node->next;
	}
	if (current_node)
	{
		prev->next = current_node->next;
		if (current_node->data)
			free(current_node->data);
		if (current_node->name)
			free(current_node->name);
		if (current_node)
			free(current_node);
	}
	else
		prev->next = NULL;
	g_global.get_nb_status = 0;
}

void	print_unset(char **name, int i)
{
	char	*res;

	res = NULL;
	g_global.get_nb_status = 1;
	ft_putstr_fd("unset", 2);
	res = ft_strjoin(name[i], ": not a valid identifier\n");
	ft_putstr_fd(res, 2);
	free(res);
}

void	ft_unset(t_env **env_v, char **name)
{
	int		i;
	t_env	*new;
	int		len;

	new = NULL;
	i = 1;
	len = ft_strlen(name[i]);
	while (name[i])
	{
		if (!check_export(name[i]))
			print_unset(name, i);
		else if (!ft_strcmp((*env_v)->name, name[i])
			&& search_element(env_v, name[i]))
		{
			new = *env_v;
			*env_v = (*env_v)->next;
			if (new)
				free(new);
		}
		else if (search_element(env_v, name[i]))
			help_unset(env_v, name, i);
		i++;
	}	
}
