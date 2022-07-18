/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_linkedlist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:04:04 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/04 22:14:00 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_lstsize(t_env *lst)
{
	unsigned int	count;
	
	count = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

t_env	*ft_lstnew(char *name, char *data)
{
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->name = name;
	res->data = data;
	res->next = NULL;
	return (res);
}
