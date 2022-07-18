/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:21:23 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/18 20:42:18 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int check_unset(char **av)
{
	int i;
	int j;

	i = 1;
	while(av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isalpha(av[i][j]))
				return(0);
			j++;
		}
		i++;
	}
	return (1);
}

void    ft_unset(t_env **env_v, char **name)
{
	t_env	*new;
	t_env	*prev;
	t_env	*current_node;
	int		i;

	i = 1;
	if (ft_isalpha(name[i][0]) || name[i][0] == '_')
	{
		if ((*env_v)->name == *name && search_element(env_v, name[i]))
		{
			new = *env_v;
			*env_v = (*env_v)->next;
			free(new);
		}
		else
		{
			while(name[i] && search_element(env_v, name[i]))
			{
				prev = *env_v;
				current_node = (*env_v)->next;
				while (current_node != NULL && ft_strcmp(current_node->name, name[i]))
				{
					prev = prev->next;
					current_node = current_node->next;
				}
				prev->next = current_node->next;
				free(current_node);
				i++;
			}
		}
		get_nb_status = 0;
	}
	else
	{
		printf("unset : %s : not a valid identifier\n", name[1]);
		get_nb_status = 1;
	}
}

