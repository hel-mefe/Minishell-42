/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:21:23 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/23 17:29:00 by ytijani          ###   ########.fr       */
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
	t_env	*new;
	t_env	*prev;

	prev = *env_v;
	current_node = (*env_v)->next;
	while (current_node != NULL && ft_strcmp(current_node->name, name[i]))
	{
		prev = prev->next;
		current_node = current_node->next;
	}
	if (current_node)
	{
		prev->next = current_node->next;
		free(current_node->data);
		free(current_node->name);
		free(current_node);
	}
	else
		prev->next = NULL;
}

void	ft_unset(t_env **env_v, char **name)
{
	int		i;
	t_env	*new;
	t_env	*prev;
	t_env	*current_node;

	i = 1;
	while (name[i])
	{
		if (!ft_isalpha(name[i][0]) && name[i][0] != '_')
		{
			printf("unset : %s : not a valid identifier\n", name[1]);
			g_global.get_nb_status = 1;
		}
		else if (!ft_strcmp((*env_v)->name, name[i])
			&& search_element(env_v, name[i]))
		{
			new = *env_v;
			*env_v = (*env_v)->next;
			free(new);
		}
		else if (search_element(env_v, name[i]))
			help_unset(env_v, name, i);
		g_global.get_nb_status = 0;
		i++;
	}	
}
