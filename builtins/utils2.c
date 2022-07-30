/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:19:56 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/30 15:26:10 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	init_spl(char **spl, char **av, int i, t_env **env_v)
{
	int	len;

	len = ft_strlen(av[i]);
	spl[1] = NULL;
	spl[0] = ft_substr(av[i], 0, (len - ft_strlen(spl[1])));
	if (!check_export(spl[0]))
	{
		print_err(av);
		free(spl[0]);
		return ;
	}
	check_evr(env_v, spl, av, 0);
	free(spl[0]);
}

int	norm_cmd(t_cmd *cmd, t_data *data, t_env **env, char **str)
{
	int	pid;
	int	v;

	pid = -1;
	v = 0;
	while (cmd)
	{
		if (cmd->next == NULL)
			pid = help_runcmd(data, cmd, env, str);
		else
			v = help_runcmd(data, cmd, env, str);
		cmd = cmd->next;
	}
	return (pid);
}
