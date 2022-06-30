#include "parsing.h"

char	*expand_result(t_data *data, char *res)
{
	t_dollar	*vars;
	char		*expanded;
	int			place;

	vars = get_all_dollars(res, data->env);
	expanded = expand_string(vars, data->env, &place, res);
	return (expanded);
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
		s = readline("heredoc> ");
        keep_res = res;
		if (!ft_strcmp(s, limiters->s))
		{
			cmd = get_command_by_id(cmds, limiters->cmd_id);
		    if (cmd && cmd->has_heredoc && (!limiters->next || limiters->next->cmd_id != cmd->cmd_id)) // last limiter that has been written in the pipe
		    {
				if (limiters->ex)
					res = expand_result(data, res);
				printf("HEREDOC RES ==> ");
				write(1, res, ft_strlen(res));
				printf("\n");
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