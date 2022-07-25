#include "../include/parsing.h"

void	alpha_except_token(t_data *data, char *s)
{
	int	i;

	if (!s || !s[i])
		data->err = SYNTAX_ERR_NEAR_NEWLINE;
	i = 0;
	while (s[i])
	{
		if (is_token(s[i]))
		{
			if (s[i] == '|')
				data->err = SYNTAX_ERR_NEAR_PIPE;
			if (s[i] == '<')
				data->err = SYNTAX_ERR_NEAR_INFILE;
			if (s[i] == '>' && s[i + 1] == '>')
				data->err = SYNTAX_ERR_NEAR_OUTFILE_APPEND;
			else if (s[i] == '>')
				data->err = SYNTAX_ERR_NEAR_OUTFILE;
			return ;
		}
		i++;
	}
}

size_t  get_heredoc(char *s, t_data *data, t_cmd *cmd)
{
    size_t  i;
    int     trigger;

    trigger = 0;
    i = 0;
    if (!s[i])
    {
        data->is_syntax_valid = 0;
        data->err = SYNTAX_ERR_NEAR_NEWLINE;
    }
    while (s[i])
    {
        while (is_space(s[i]))
            i++;
        if (s[i] == '<' && s[i + 1] == '<' && trigger)
            i += 2;
        else if (trigger)
            return (i);
        catch_syntax_err(data, s + i);
        if (data->err)
            break ;
        i += get_string(s + i, HERE_DOC, data, cmd);
        trigger = 1;
    }
    return (i);
}