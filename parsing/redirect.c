/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:51:45 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:10:31 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	get_instructions(t_data *data, t_cmd *cmd, int pipe_index)
{
	if (cmd->error < 0)
	{
		if (cmd->write_end == -1)
		{
			if (pipe_index == data->n_cmds - 1)
				cmd->write_end = 1;
			else
				cmd->write_end = data->pipes[pipe_index][1];
		}
		if (cmd->read_end == -1)
		{
			if (pipe_index == 0 && !cmd->has_heredoc)
				cmd->read_end = 0;
			else if (cmd->has_heredoc)
			{
				pipe(cmd->heredoc_pipe);
				cmd->read_end = cmd->heredoc_pipe[0];
			}
			else
				cmd->read_end = data->pipes[pipe_index - 1][0];
		}
	}
}

void	prepare_data(t_data *data)
{
	int		i;
	t_cmd	*cmd;

	data->pipes = (int **) malloc (data->n_cmds * sizeof(int *));
	data->pipes[data->n_cmds - 1] = NULL;
	cmd = data->commands;
	i = 0;
	while (i < data->n_cmds)
	{
		if (i < data->n_cmds - 1)
		{
			data->pipes[i] = (int *) malloc(2 * sizeof(int));
			pipe(data->pipes[i]);
		}
		get_instructions(data, cmd, i);
		cmd = cmd->next;
		i++;
	}
}
