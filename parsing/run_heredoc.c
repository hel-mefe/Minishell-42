#include "parsing.h"

char	*expand_result(t_data *data, char *res)
{
	t_dollar	*vars;
	char		*expanded;
	int			place;

	if (!res)
		return (NULL);
	vars = get_all_dollars(res, data->env);
	expanded = expand_string(vars, data->env, &place, res);
	return (expanded);
}

void	read_file(int fd)
{
	char	c;
	int i;

	i = 0;
	c = 0;
	while (read(fd, &c, 1) > 0)
	{
		i++;
		write(1, &c, 1);
	}
	printf("GOT HERE %d\n", i);
}

void	run_heredoc(t_data *data, t_queue *limiters, t_cmd *cmds)
{
	char	*s;
	char	*res;
	char	*keep_res;
	t_cmd	*cmd;

	res = NULL;
	while (limiters)
	{
		ft_putstr("heredoc> ");
		// s = readline("heredoc> ");
		s = get_next_line(0);
        keep_res = res;
		if (!ft_strcmp(s, limiters->s))
		{
			cmd = get_command_by_id(cmds, limiters->cmd_id);
		    if (cmd && cmd->has_heredoc && (!limiters->next || limiters->next->cmd_id != cmd->cmd_id)) // last limiter that has been written in the pipe
		    {
				if (limiters->ex)
					res = expand_result(data, res);
				write(cmd->heredoc_pipe[1], res, ft_strlen(res));
				close(cmd->heredoc_pipe[1]);
				read_file(cmd->heredoc_pipe[0]);
			}
			res = NULL;
		    limiters = limiters->next;
		}
		else
			res = ft_strjoin(res, s);
		if (keep_res)
			free(keep_res);
	}
}