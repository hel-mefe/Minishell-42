/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:31:44 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/25 20:17:24 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

//***************************Help_cd*****************************************//
void	help_cd(t_env **env_v, t_env *current_node, t_env *prev, char *name)
{
	prev = *env_v;
	current_node = (*env_v)->next;
	while (current_node != NULL && ft_strcmp(current_node->name, name))
	{
		prev = prev->next;
		current_node = current_node->next;
	}
	if (current_node)
	{
		prev->next = current_node->next;
		free(current_node->name);
		free(current_node->data);
		free(current_node);
	}
	else
			prev->next = NULL;
}

void	remove_name(t_env **env_v, char *name)
{
	t_env	*new;
	t_env	*prev;
	t_env	*current_node;

	if (!ft_strcmp((*env_v)->name, name))
	{
		new = *env_v;
		*env_v = (*env_v)->next;
		free(new);
	}
	else
		help_cd(env_v, current_node, prev, name);
}

//***************************Help_export*******************//
int	check_oper(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (((av[i][j] == '+' && av[i][j + 1] != '=') || av[i][j] == '-' ||
						(av[i][j] > 91 && av[i][j] < 96)) && av[i][j] != '_')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
