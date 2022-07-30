/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buckets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:09:26 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:09:27 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	put_infile(t_cmd *cmd, char *infile_name)
{
	if (cmd->error < 0)
	{
		if (cmd->infile)
		{
			free(cmd->infile);
			cmd->infile = NULL;
		}
		close(cmd->read_end);
		cmd->infile = infile_name;
		cmd->read_end = open(cmd->infile, O_RDONLY);
		if (cmd->read_end < 0)
		{
			cmd->error_file = infile_name;
			cmd->error = errno;
		}
		cmd->has_heredoc = 0;
	}
	else
		free(infile_name);
}

void	put_outfile(t_cmd *cmd, char *outfile_name)
{
	if (cmd->error < 0)
	{
		if (cmd->outfile)
		{
			free(cmd->outfile);
			cmd->outfile = NULL;
		}
		close(cmd->write_end);
		cmd->outfile = outfile_name;
		if (cmd->outfile_mode == O_APPEND)
			cmd->write_end = open(cmd->outfile, O_WRONLY | \
			O_CREAT | O_APPEND, 0644);
		else
			cmd->write_end = open(cmd->outfile, O_WRONLY | \
			O_CREAT | O_TRUNC, 0644);
		if (cmd->write_end < 0)
		{
			cmd->error = errno;
			cmd->error_file = outfile_name;
		}
	}
	else
		free(outfile_name);
}

void	put_heredoc(t_data *data, t_cmd *cmd, int place, char *limiter)
{
	t_queue	*new;

	if (cmd->read_end > 0)
		close(cmd->read_end);
	cmd->has_heredoc = 1;
	new = new_queue_node(limiter);
	new->s = limiter;
	new->ex = 0;
	if (place == EXPANDED_HERE_DOC)
		new->ex = 1;
	cmd->read_end = -1;
	new->cmd_id = cmd->cmd_id;
	push_back(&data->heredoc, new);
}

void	put_argument(t_cmd *cmd, char *argument)
{
	t_queue	*new;

	new = new_queue_node(argument);
	push_back(&cmd->args, new);
}

void	put_command(t_cmd *cmd, char *cmd_name)
{
	cmd->cmd_name = cmd_name;
}
