#include "../include/parsing.h"

void	assign_string(char *s, int place, t_data *data, t_cmd *cmd)
{
	t_queue	*new;

	if (place == INFILE && cmd->error < 0)
		put_infile(cmd, s);
	else if (place == COMMAND)
		put_command(cmd, s);
	else if (place == OUTFILE && cmd->error < 0)
		put_outfile(cmd, s);
	else if (place == HERE_DOC || place == EXPANDED_HERE_DOC)
		put_heredoc(data, cmd, place, s);
	else if (place == ARGUMENT)
		put_argument(cmd, s);
	return ;
}

char	*get_expansion(t_data *data, int *place, char *s, char *res)
{
	t_dollar	*variables;
	char		*expanded;

	if (s[0] == '\'')
	{
		variables = get_all_dollars(s, data->env, data->main_env);
		expanded = expand_string(variables, data->env, place, res);
	}
	else
		expanded = ft_strdup(res);
	if (*place == NONE_AMBIGUOUS)
		data->err = AMBIGUOUS_ERR;
	else
		data->err = NULL;
	return (expanded);
}

char	*clean_string(char *res, char *expanded_res, int *place)
{
	char	*k_res;

	k_res = expanded_res;
	expanded_res = remove_quotes(ft_strdup(expanded_res));
	free(k_res);
	if (ft_strlen(expanded_res) == ft_strlen(res) && *place == HERE_DOC)
		*place = EXPANDED_HERE_DOC;
	free(res);
	return (expanded_res);
}

size_t	get_string(char *s, int place, t_data *data, t_cmd *cmd)
{
	size_t	i;
	char	*res;
	char	*expanded_res;

	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	if (s[i] == '\"')
		res = get_doubly_string(s + i, cmd);
	else if (s[i] == '\'')
		res = get_singly_string(s + i, cmd);
	else
		res = get_normal_string(s + i, cmd);
	expanded_res = get_expansion(data, &place, s + i, res);
	i += ft_strlen(res);
	expanded_res = clean_string(res, expanded_res, &place);
	assign_string(expanded_res, place, data, cmd);
	return (i);
}