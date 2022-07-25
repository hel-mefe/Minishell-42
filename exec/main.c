/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:22:53 by marvin            #+#    #+#             */
/*   Updated: 2022/07/20 19:35:55 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	handel_sigint(int sig)
{
	if (sig == SIGINT && g_global.get_nb == 0)
	{
		g_global.get_nb_status = 1;
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT && g_global.get_nb == 1)
	{		
		g_global.new = dup(0);
		g_global.get_nb_status = 1;
		g_global.get_nb = -1;
		printf("\n");
		close(0);
	}
}

void	handle_signals(void)
{
	signal(SIGINT, handel_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	run_builtin(t_env **env_v, char **av)
{
	if ((ft_strcmp(av[0], "echo")) == 0)
		ft_echo(env_v, av);
	else if ((ft_strcmp(av[0], "pwd")) == 0)
		ft_pwd(env_v);
	else if ((ft_strcmp(av[0], "cd")) == 0)
		ft_cd(env_v, av);
	else if ((ft_strcmp(av[0], "env")) == 0)
		ft_env(env_v, av);
	else if ((ft_strcmp(av[0], "export")) == 0)
		ft_export(env_v, av);
	else if ((ft_strcmp(av[0], "unset")) == 0)
		ft_unset(env_v, av);
	else if ((ft_strcmp(av[0], "exit")) == 0)
		ft_exit(av);
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

// int main(int ac, char **av, char **env)
// {
//     char    *s;
//     t_env   *env_v;
//     t_data  *data;

//     (void)av;
//     (void)ac;
// 	env_v = NULL;
//     init_env(&env_v, env);
//     while (1)
//     {
//       	s = readline("minishell> ");
// 	    handle_signals();
// 		if (s == NULL)
// 		{
// 			printf("exit\n");
// 			exit(0);
// 		}
// 		if (s != NULL && s[0])
// 		{
//         	add_history(s);
//        		data = parse_line(s, env, env_v);
// 			run_heredoc(data, data->heredoc, data->commands);
// 			if (!data->err)
// 				run_cmd(&env_v, data, data->commands);
// 			else
// 				printf("%s\n", data->err);
// 			destory_data(&data);
// 			data = NULL;
// 		}
//     }
// }
