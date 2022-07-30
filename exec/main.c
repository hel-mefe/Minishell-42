/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:22:53 by marvin            #+#    #+#             */
/*   Updated: 2022/07/30 00:25:25 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	run_builtin(t_env **env_v, char **av, t_cmd *cmd)
{
	if ((ft_strcmp(av[0], "echo")) == 0)
		ft_echo(env_v, av, cmd->write_end);
	else if ((ft_strcmp(av[0], "pwd")) == 0)
		ft_pwd(env_v);
	else if ((ft_strcmp(av[0], "cd")) == 0)
		ft_cd(env_v, av);
	else if ((ft_strcmp(av[0], "env")) == 0)
		ft_env(env_v, av, cmd->write_end);
	else if ((ft_strcmp(av[0], "export")) == 0)
		ft_export(env_v, av, cmd->write_end);
	else if ((ft_strcmp(av[0], "unset")) == 0)
		ft_unset(env_v, av);
	else if ((ft_strcmp(av[0], "exit")) == 0)
		ft_exit(av);
}

void	help_runbuilt(t_cmd *cmd, t_env **env, int res, char **str)
{
	res = dup(0);
	if (cmd->error == 0)
	{
		g_global.get_nb_status = 1;
		ft_putstr_fd(AMBIGUOUS_ERR, 2);
		return ;
	}
	if (cmd->error > 0)
	{
		g_global.get_nb_status = 1;
		ft_putstr_fd(strerror(cmd->error), 2);
		ft_putstr_fd("\n", 2);
		dup(res);
		close(res);
		return ;
	}
	run_builtin(env, cmd->main_args, cmd);
	if (str)
		free_double_char_arr(str);
	dup(res);
	close(res);
}

void	close_pipe(int **pipes, int a, int b, int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		if (pipes[i][0] != a)
			close(pipes[i][0]);
		if (pipes[i][1] != b)
			close(pipes[i][1]);
		i++;
	}
	dup2(a, 0);
	dup2(b, 1);
}

void	print_in_fd(char *s, int fd)
{
	char	*res;

	res = NULL;
	res = ft_strjoin(s, "\n");
	ft_putstr_fd(res, fd);
	free(res);
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	t_env	*env_v;
	t_data	*data;
	int		history;
	char	*res;

	(void)av;
	(void)ac;
	env_v = NULL;
	init_env(&env_v, env);
	history = open(".minishell_History", O_CREAT | O_RDWR | O_APPEND, 0644);
	get_line(history, s);
	while (1)
	{
		handle_signals(0);
		s = show_prompt(env_v);
		if (s)
			print_in_fd(s, history);
		check_cmd(&env_v, s, env, data);
		free(s);

	}
	close(history);
}
