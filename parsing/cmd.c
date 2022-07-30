/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:50:43 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/29 22:50:44 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

size_t	get_quote_end(char *s, char c)
{
	size_t	i;
	int		end;

	end = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			end = i;
		if (s[i] == c && (!s[i + 1] || is_space(s[i + 1]) || s[i + 1] == '|'))
			break ;
		i++;
	}
	return (end);
}

int	lookup_for_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_space(s[i]) && s[i] != '|')
			return (1);
		i++;
	}
	return (0);
}

int	try_command_push(t_data *data, t_cmd **head, char *s, size_t *s_end)
{
	t_cmd	*new;

	if (s[s_end[1]] == '|')
		get_pipe_err(data, s, s_end[1]);
	if (s[s_end[1]] == '|' && !lookup_for_char(s + s_end[1] + 1))
		data->err = UNCLOSED_PIPE_ERR;
	new = new_command(*head);
	if (!s[s_end[1] + 1] && s[s_end[1]] != '|')
		new->line = slice(s, s_end[0], s_end[1] + 1);
	else
		new->line = slice(s, s_end[0], s_end[1]);
	push_command(head, new);
	if (data->err)
		return (0);
	return (1);
}

t_cmd	*get_commands(t_data *data, char *s)
{
	size_t	s_end[2];
	t_cmd	*head;

	s_end[0] = 0;
	s_end[1] = -1;
	head = NULL;
	while (s[++s_end[1]])
	{
		if (s[s_end[1]] == '\'')
			s_end[1] += get_quote_end(s + s_end[1] + 1, '\'') + 1;
		else if (s[s_end[1]] == '\"')
			s_end[1] += get_quote_end(s + s_end[1] + 1, '\"') + 1;
		if (s[s_end[1]] == '|' || !s[s_end[1] + 1])
		{
			if (!try_command_push(data, &head, s, s_end))
				break ;
			s_end[0] = s_end[1] + 1;
		}
	}
	return (head);
}
