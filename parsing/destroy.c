/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:50:47 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/29 22:50:48 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	free_str(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	free_commands(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_str(&cmd->line);
	free_str(&cmd->cmd_name);
	free_str(&cmd->infile);
	free_str(&cmd->outfile);
	free_queue(cmd->args);
	free_double_char_arr(cmd->main_args);
	free_dollars(cmd->vars);
	if (cmd->heredoc_pipe[0] > 0)
		close(cmd->heredoc_pipe[0]);
	if (cmd->heredoc_pipe[1] > 0)
		close(cmd->heredoc_pipe[1]);
	free_commands(cmd->next);
	free(cmd);
}

void	destory_data(t_data **data)
{
	free_queue((*data)->heredoc);
	(*data)->heredoc = NULL;
	free_commands((*data)->commands);
	close_pipes((*data)->pipes, (*data)->n_cmds - 1);
	(*data)->commands = NULL;
	free((*data)->pipes);
	free(*data);
	*data = NULL;
}
