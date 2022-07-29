/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:01:36 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/30 00:28:22 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	check_err(t_cmd *cmd)
{
	if (cmd->error_file)
	{
		ft_putstr_fd(ft_strdup(cmd->error_file), 2);
		ft_putstr_fd(ft_strdup(": "), 2);
	}
	if (cmd->error == 0)
		ft_error1(1, AMBIGUOUS_ERR);
	if (cmd->error > 0)
		ft_error1(1, strerror(cmd->error));
}

void	get_line(int history, char *s)
{
	s = get_next_line(history);
	if (s)
	{
		free(s);
		s = ft_strtrim(s, "\n");
		add_history(s);
	}
	while (s)
	{
		free(s);
		s = get_next_line(history);
		if (s)
		{
			free(s);
			s = ft_strtrim(s, "\n");
			add_history(s);
		}
	}
	free(s);
}

void	check_cmd(t_env *env_v, char *s, char	**env, t_data *data)
{
	if (s == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (s != NULL && s[0])
	{
		add_history(s);
		data = parse_line(s, env, env_v);
		if (get_queue_size(data->heredoc) > HERE_DOC_MAX)
			get_err(MAX_HERE_DOC_EXCEEDED_ERR, 1);
		run_heredoc(data, data->heredoc, data->commands);
		if (data->err)
		{
			g_global.get_nb_status = 258;
			get_err(data->err, 0);
			destory_data(&data);
			return ;
		}
		if (data->n_cmds == 1 && !data->commands->cmd_name)
		{
			destory_data(&data);
			return ;
		}
		if (data->is_syntax_valid)
			run_cmd(&env_v, data, data->commands);
		destory_data(&data);
		data = NULL;
	}
}

int	check_export(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (ft_isdigit(str[0]) || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '+' && !str[i + 1])
			return (1);
		if ((!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}
