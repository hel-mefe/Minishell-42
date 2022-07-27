/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 10:01:36 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/27 11:24:46 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

//*******************Hellp_function_main******//
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
		run_heredoc(data, data->heredoc, data->commands);
		if (data->err)
		{
			g_global.get_nb_status = 258;
			printf("%s\n", data->err);
		}
		if (data->is_syntax_valid)
			run_cmd(&env_v, data, data->commands);
		destory_data(&data);
		data = NULL;
	}
}
