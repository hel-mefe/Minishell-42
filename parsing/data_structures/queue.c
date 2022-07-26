/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 22:45:12 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/25 23:02:48 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

size_t	get_queue_size(t_queue *head)
{
	if (!head)
		return (0);
	return (get_queue_size(head->next) + 1);
}

t_queue	*new_queue_node(char *s)
{
	t_queue	*new;

	new = (t_queue *) malloc (sizeof(t_queue));
	if (!new)
		return (NULL);
	new->s = s;
	return (new);
}

t_queue	*get_last(t_queue *head)
{
	if (!head)
		return (NULL);
	if (!head->next)
		return (head);
	return (get_last(head->next));
}

void	push_back(t_queue **head, t_queue *new)
{
	t_queue	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last(*head);
		last->next = new;
	}
	new->next = NULL;
}
