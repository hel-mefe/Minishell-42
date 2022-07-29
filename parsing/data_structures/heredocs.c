/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:52:10 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/29 22:52:11 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_heredoc	*new_heredoc(void)
{
	t_heredoc	*new;

	new = (t_heredoc *) malloc (sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->limiters = NULL;
	return (new);
}

t_heredoc	*get_last_heredoc(t_heredoc *head)
{
	if (!head)
		return (NULL);
	if (!head->next)
		return (head);
	return (get_last_heredoc(head->next));
}

void	push_heredoc_back(t_heredoc **head, t_heredoc *new)
{
	t_heredoc	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_heredoc(*head);
		last->next = new;
	}
	new->next = NULL;
}
