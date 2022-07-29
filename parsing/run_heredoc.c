
#include "../include/parsing.h"

char	*expand_result(t_data *data, char *res)
{
	t_dollar	*vars;
	char		*expanded;
	int			place;

	if (!res)
		return (NULL);
	vars = get_all_dollars(res, data->env, data->main_env);
	expanded = expand_string(vars, data->env, &place, res);
	free_dollars(vars);
	return (expanded);
}

void	limiter_found(t_data *data, t_queue **limiters, char **res)
{
	t_cmd	*cmd;
	char	*keep_res;

	cmd = get_command_by_id(data->commands, (*limiters)->cmd_id);
	if (cmd && cmd->has_heredoc && \
	(!(*limiters)->next || (*limiters)->next->cmd_id != cmd->cmd_id))
	{
		if ((*limiters)->ex)
		{
			keep_res = *res;
			*res = expand_result(data, *res);
			free(keep_res);
		}
		write(cmd->heredoc_pipe[1], *res, ft_strlen(*res));
		close(cmd->heredoc_pipe[1]);
	}
	if (*res)
		free(*res);
	(*limiters) = (*limiters)->next;
	*res = NULL;
}

void	limiter_not_found(char **res, char **s)
{
	*res = ft_strjoin_free(*res, *s);
	*res = ft_strjoin_free(*res, ft_strdup("\n"));
}

void	run_heredoc(t_data *data, t_queue *limiters, t_cmd *cmds)
{
	char	*s;
	char	*res;
	char	*keep_res;
	t_cmd	*cmd;
	int		trigger;

	trigger = 0;
	res = NULL;
	handle_signals(1);
	g_global.new = dup(0);
	while (limiters)
	{
		g_global.get_nb = 1;
		s = readline("haredoc> ");
		if (s == NULL)
			g_global.get_nb = -1;
		if (g_global.get_nb == -1)
		{
			g_global.get_nb = 0;
			trigger = 1;
			break;
		}
		if (!ft_strcmp(s, limiters->s))
		{
			limiter_found(data, &limiters, &res);
			free(s);
		}
		else
			limiter_not_found(&res, &s);
	}
	if (trigger)
	{
		t_cmd *cmd = get_command_by_id(data->commands, limiters->cmd_id);
		if (s)
			free(s);
		if (res)
			free(res);
		close(cmd->heredoc_pipe[1]);
	}
	dup2(g_global.new, 0);
}
