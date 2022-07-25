#include "../parsing.h"
#include "../../exec/mini.h"

char	*expand_result(t_data *data, char *res)
{
	t_dollar	*vars;
	char		*expanded;
	int			place;

	if (!res)
		return (NULL);
	vars = get_all_dollars(res, data->env, data->main_env);
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
	global.get_nb = 0;
	while (limiters)
	{
		global.get_nb = 1;
		s = readline("haredoc> ");
		handle_signals();
		if (global.get_nb == -1)
			break ;
		if (!ft_strcmp(s, limiters->s))
		{
			cmd = get_command_by_id(cmds, limiters->cmd_id);
		    if (cmd && cmd->has_heredoc && (!limiters->next || limiters->next->cmd_id != cmd->cmd_id)) // last limiter that has been written in the pipe
		    {
				if (limiters->ex)
				{
					keep_res = res;
					res = expand_result(data, res);
					free(keep_res);
				}
				write(cmd->heredoc_pipe[1], ft_strjoin(res,"\n"), ft_strlen(res) + 1);
				close(cmd->heredoc_pipe[1]);
			}
			if (res)
				free(res);
			res = NULL;
		    limiters = limiters->next;
		}
		else
			res = ft_strjoin_free(res, s);
	}
	dup(global.new);
}

size_t  get_heredoc(char *s, t_data *data, t_cmd *cmd)
{
    size_t  i;
    int     trigger;

    trigger = 0;
    i = 0;
    is_there_any_alpha(data, s + i, 1);
    if (data->err)
        return (i);
    while (s[i])
    {
        while (is_space(s[i]))
            i++;
        if (s[i] == '<' && s[i + 1] == '<' && trigger)
            i += 2;
        is_there_any_alpha(data, s + i, 1);
        if (data->err)
            break ;
        else if (trigger)
            return (i);
        i += get_string(s + i, HERE_DOC, data, cmd);
        trigger = 1;
    }
    return (i);
}