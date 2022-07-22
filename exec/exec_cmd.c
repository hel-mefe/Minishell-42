/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:01:19 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/22 16:46:26 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	wait_close(t_data *data, t_cmd *tmp)
{
	int	i;

	i = 0;
	while (i < data->n_cmds - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	while (tmp)
	{
		if ((waitpid(-1, &tmp->status, WUNTRACED)) < 0)
			perror("waitpid");
		if (WIFEXITED(tmp->status))
			g_global.get_nb_status  = WEXITSTATUS(tmp->status);
		tmp = tmp->next;
	}
}

void	help_runcmd(t_data *data, t_cmd *cmd, t_env **env, char **str)
{
	pid_t	pid;

	pid = fork();
	// signal(SIGQUIT, SIG_DFL);
	// signal(SIGINT, SIG_DFL);
	if (pid < 0)
	{
		printf("pipe Error\n");
		g_global.get_nb_status = 127;
	}
	else if (pid == 0)
	{
		close_pipe(data->pipes, cmd->read_end, cmd->write_end, data->n_cmds);
		if (cmd->is_builtin)
		{
			run_builtin(env, cmd->main_args);
			exit(g_global.get_nb_status);
		}
		if (cmd->error > 0)
		{
			ft_error1(-1, strerror(cmd->error));
			write(1,"\n", 1);
		}
		ever(cmd->main_args, env, str, data);
	}
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

void	ever(char **cmd, t_env **env_v, char **env, t_data *data)
{
	if (execve(get_command(env_v, *cmd), cmd, env) == -1)
	{

		if (strstr(cmd[0], "/"))
			ft_error1(-1, ft_strjoin(*cmd, ": no such file or directory\n"));
		else
			ft_error1(-1, ft_strjoin(*cmd, ": command not found\n"));
	}
}

void	run_cmd(t_env **env, t_data *data, t_cmd *cmd)
{	
	int		i;
	t_cmd	*tmp;
	char	**str;

	str = change_env(env);
	tmp = cmd;
	if (cmd->is_builtin && cmd->next == NULL)
	{
		run_builtin(env, cmd->main_args);
		free_double_char_arr(str);
		return ;
	}
	while (cmd)
	{
		help_runcmd(data, cmd, env, str);
		cmd = cmd->next;
	}
	free_double_char_arr(str);
	wait_close(data, tmp);
	handle_signals();
}
