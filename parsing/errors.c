#include "../include/parsing.h"

void	catch_syntax_err(t_data *data, char *s)
{
	size_t	i;

	if (!s)
	{
		data->is_syntax_valid = 0;
		data->err = SYNTAX_ERR_NEAR_NEWLINE;
		return ;
	}
	i = 0;
	while (s[i])
	{
		if (!is_token(s[i]) && !is_space(s[i]))
			return ;
		if (is_token(s[i]))
		{
			if (s[i] == '>' && s[i + 1] == '>')
				data->err = SYNTAX_ERR_NEAR_OUTFILE_APPEND;
			else if (s[i] == '>')
				data->err = SYNTAX_ERR_NEAR_OUTFILE;
			if (s[i] == '<' && s[i + 1] == '<')
				data->err = SYNTAX_ERR_NEAR_HEREDOC;
			else if (s[i] == '<')
				data->err = SYNTAX_ERR_NEAR_INFILE;
			if (s[i] == '|')
				data->err = SYNTAX_ERR_NEAR_PIPE;
			data->is_syntax_valid = 0;
			return ;
		}
		i++;
	}
	data->is_syntax_valid = 0;
	data->err = SYNTAX_ERR_NEAR_NEWLINE;
}

void    get_err(char *err, int is_exit)
{
    size_t  i;

    i = -1;
    while (err[++i])
        write(2, &err[i], 1);
    if (is_exit)
        exit(EXIT_FAILURE);
}