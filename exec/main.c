/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:22:53 by marvin            #+#    #+#             */
/*   Updated: 2022/06/27 15:07:59 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handel_sigint(int sig)
{
	(void)sig;
	write(1,"\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals()
{
	signal(SIGINT, handel_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void    run_builtin(t_env **env_v, char **av)
{
    if ((ft_strcmp(av[0], "echo")) == 0)
        ft_echo(av);
    else if ((ft_strcmp(av[0],"pwd")) == 0)
        ft_pwd(env_v);
    else if ((ft_strcmp(av[0],"cd")) == 0)
        ft_cd(env_v, av);
    else if ((ft_strcmp(av[0],"env")) == 0)
        ft_env(env_v, av);
    else if ((ft_strcmp(av[0], "export")) == 0)
        ft_export(env_v, av);
    else if ((ft_strcmp(av[0], "unset")) == 0)
        ft_unset(env_v,av );
}

void	close_pipe(int **pipes, int a, int b, int n)
{
	int	i;

	i = 0;
	dup2(a, 0);
	dup2(b, 1);
	while (i < n - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
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
	while(new)
	{
		buffer = ft_strjoin(new->name, "=");
		res[i] = ft_strjoin(buffer,new->data);
		free(buffer);
		new = new->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

void	ever(char **cmd, t_env **env_v, char **env, t_data *data)
{
	if (get_command(env_v, *cmd) == NULL)
	{
		if (data->commands->has_heredoc)
			exit(0);
	}
	if (execve(get_command(env_v, *cmd), cmd, env) == -1)
	{
		if (strstr(cmd[0], "/"))
			ft_error1(-1, ft_strjoin(*cmd,": no such file or directory\n"));
		else
			ft_error1(-1, ft_strjoin(*cmd, ": command not found\n"));
	}
}

void    run_cmd(t_env **env, t_data *data, t_cmd *cmd)
{	
	int 	i;
	t_cmd	*tmp;
	char	**str;
	pid_t	pid;
	
	str = change_env(env);
	tmp = cmd;
	if (cmd->is_builtin && cmd->next == NULL)
	{
		run_builtin(env, cmd->main_args);
			free_double_char_arr(str);
		return ;
	}
    while(cmd)
    {
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid < 0)
		{
			printf("pipe Error\n");
			get_nb_status = 127;
		}
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
        	close_pipe(data->pipes, cmd->read_end, cmd->write_end, data->n_cmds);
			if (cmd->is_builtin && cmd->next != NULL)
			{
				run_builtin(env, cmd->main_args);
				exit(get_nb_status);
			}
			if (cmd->error > 0)
				ft_error1(-1, strerror(cmd->error));
			ever(cmd->main_args, env, str, data);
		}
		cmd = cmd->next;
    }
	free_double_char_arr(str);
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
		if (WEXITSTATUS(tmp->status))
			get_nb_status = WEXITSTATUS(tmp->status);
		tmp = tmp->next;
	}
	handle_signals();
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char    *s;
    t_env   *env_v;
    t_data  *data;

	env_v = NULL;
    init_env(&env_v, env);
	handle_signals();
    while (1)
    {
        s = readline("minishell> ");
		if (s == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (s != NULL && s[0])
		{
        	add_history(s);
       		data = parse_line(s, env, env_v);
			printf("*********************************************\n");
			run_heredoc(data, data->heredoc, data->commands);
       		run_cmd(&env_v, data, data->commands);
			destory_data(&data);
			free(s);
			free(data);
			data = NULL;
		}
    }
}
