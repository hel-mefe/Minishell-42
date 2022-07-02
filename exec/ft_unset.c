/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:21:23 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/01 21:33:05 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void    ft_unset(t_env **env_v, char *name)
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
