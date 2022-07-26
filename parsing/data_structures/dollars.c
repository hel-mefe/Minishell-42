/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:04:40 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/25 23:06:12 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_dollar	*new_dollar(char *var, char *val)
{
	t_dollar	*new;

	new = (t_dollar *) malloc (sizeof(t_dollar));
	if (!new)
		return (NULL);
	new->var = var;
	new->val = val;
	return (new);
}

t_dollar	*get_last_dollar(t_dollar *head)
{
	if (!head)
		return (NULL);
	if (!head->next)
		return (head);
	return (get_last_dollar(head->next));
}

void	push_back_dollar(t_dollar **head, t_dollar *new)
{
	t_dollar	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_dollar(*head);
		last->next = new;
	}
	new->next = NULL;
}
