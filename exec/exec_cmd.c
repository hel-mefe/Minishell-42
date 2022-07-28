/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:01:19 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/28 23:49:54 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	wait_close(t_data *data, t_cmd *tmp, int pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->n_cmds - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	if (pid != -1)
	{
		if ((waitpid(pid, &tmp->status, 0)) < 0)
			perror("waitpid");
		if (WIFEXITED(tmp->status))
			g_global.get_nb_status = WEXITSTATUS(tmp->status);
	}
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(tmp->status))
		g_global.get_nb_status = WEXITSTATUS(tmp->status);
}

int	help_runcmd(t_data *data, t_cmd *cmd, t_env **env, char **str)
{
	int	pid;
	int	i;

	i = 0;
	pid = fork();
	handle_signals(1);
	if (pid < 0)
	{
		ft_putstr_fd("pipe Error\n", 2);
		g_global.get_nb_status = 127;
	}
	else if (pid == 0)
	{
		close_pipe(data->pipes, cmd->read_end, cmd->write_end, data->n_cmds);
		if (cmd->is_builtin)
		{
			run_builtin(env, cmd->main_args, cmd);
			exit(g_global.get_nb_status);
		}
		check_err(cmd);
		ever(cmd->main_args, env, str);
	}
	return (pid);
}

char	**change_env(t_env **env_v)
{
	t_env	*new;
	char	**res;
	char	*buffer;
	int		len;
	int		i;

	new = *env_v;
	i = 0;
	len = ft_lstsize(new);
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	while (new)
	{
		buffer = ft_strjoin(new->name, "=");
		res[i] = ft_strjoin(buffer, new->data);
		free(buffer);
		new = new->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

void	ever(char **cmd, t_env **env_v, char **env)
{
	if (execve(get_command(env_v, *cmd), cmd, env) == -1)
	{
		if (strstr(cmd[0], "/"))
			ft_error1(-1, ft_strjoin(*cmd, ": no such file or directory"));
		else
			ft_error1(-1, ft_strjoin(*cmd, ": command not found"));
	}
}

void	run_cmd(t_env **env, t_data *data, t_cmd *cmd)
{	
	t_cmd	*tmp;
	char	**str;
	int		res;
	int		pid;
	int		v;

	str = change_env(env);
	tmp = cmd;
	pid = -1;
	res = 0;
	if (cmd->is_builtin && cmd->next == NULL)
	{
		help_runbuilt(cmd, env, res, str);
		return ;
	}
	while (cmd)
	{
		if (cmd->next == NULL)
			pid = help_runcmd(data, cmd, env, str);
		else
			v = help_runcmd(data, cmd, env, str);
		cmd = cmd->next;
	}
	wait_close(data, tmp, pid);
	free_double_char_arr(str);
}
