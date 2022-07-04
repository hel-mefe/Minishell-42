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
        ft_pwd();
    else if ((ft_strcmp(av[0],"cd")) == 0)
        ft_cd(env_v, av);
    else if ((ft_strcmp(av[0],"env")) == 0)
        ft_env(env_v, av);
    else if ((ft_strcmp(av[0], "export")) == 0)
        ft_export(env_v, av);
    else if ((ft_strcmp(av[0], "unset")) == 0)
        ft_unset(env_v, av[1]);
}

int	check_infile(t_cmd *cmd)
{
	if (cmd->has_heredoc)
		return (cmd->heredoc_pipe[0]);
	else
		return(cmd->read_end);
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
	len = ft_lstsize(*env_v);
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	while(new)
	{
		res[i] = new->name;
		// buffer = ft_strjoin(new->name, "=");
		// res[i] = ft_strjoin(buffer, new->data);
		new = new->next;
		i++;
	}
	res[i] = 0;
	return (res);
}

void	ever(char **cmd, t_env **env_v, char **env)
{
	char	*path;

	path = get_command(env_v, *cmd);
	if (!path)
		exit(127);
	if (execve(get_command(env_v, *cmd), cmd, env) == -1)
	{
		if (strstr(cmd[0], "/"))
			ft_error1(-1, "no such file or directory\n");
		else
			ft_error1(-1, "command not found\n");
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
			printf("HAS_HEREDOC IN CMD ==> %d\n", cmd->has_heredoc);
			if (cmd->error > 0)
				ft_error1(-1, strerror(cmd->error));
			if (cmd->is_builtin && cmd->next != NULL)
				run_builtin(env, cmd->main_args);
			
			ever(cmd->main_args, env,str);
		}
		cmd = cmd->next;
    }
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


// int main(int ac, char **av, char **env)
// {
//     (void)ac;
//     (void)av;
//     char    *s;
//     t_env   *env_v;
//     t_data  *data;

//     init_env(&env_v, env);
// 	handle_signals();
//     while (1)
//     {
//         add_history(s);
//         s = readline("minishell> ");
// 		if (s == NULL)
// 		{
// 			printf("exit\n");
// 			exit(0);
// 		}
//         data = parse_line(s, env);
// 		run_heredoc(data, data->heredoc, data->commands);
//        	run_cmd(&env_v, data, data->commands);
//          //print_commands(data->commands);
//         // print_heredoc(data->heredoc);
//         free_queue(data->heredoc);
// 		free(data);
//     }
// }
