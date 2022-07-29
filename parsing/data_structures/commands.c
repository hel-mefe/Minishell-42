/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:51:58 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/29 22:51:59 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	get_commands_size(t_cmd *head)
{
	if (!head)
		return (0);
	return (1 + get_commands_size(head->next));
}

t_cmd	*get_command_by_id(t_cmd *head, int id)
{
	while (head)
	{
		if (head->cmd_id == id)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_cmd	*get_last_command(t_cmd *head)
{
	if (!head)
		return (NULL);
	if (!head->next)
		return (head);
	return (get_last_command(head->next));
}

t_cmd	*new_command(t_cmd *head)
{
	t_cmd	*new;

	new = (t_cmd *) malloc (sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->syntax = NULL;
	new->main_args = NULL;
	new->outfile_mode = O_CREAT;
	new->vars = NULL;
	new->cmd_name = NULL;
	new->line = NULL;
	new->is_builtin = 0;
	new->error_file = NULL;
	new->cmd_id = get_commands_size(head) + 1;
	new->error = -1;
	new->write_end = -1;
	new->read_end = -1;
	return (new);
}

void	push_command(t_cmd **head, t_cmd *new)
{
	t_cmd	*last;

	if (!(*head))
	{
		*head = new;
		new->prev = NULL;
	}
	else
	{
		last = get_last_command(*head);
		last->next = new;
		new->prev = last;
	}
	new->next = NULL;
}
