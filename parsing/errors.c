#include "../include/parsing.h"

void	set_syntax_error(t_data *data, char c, char next_c)
{
	if (c == '>' && next_c == '>')
		data->err = SYNTAX_ERR_NEAR_OUTFILE_APPEND;
	else if (c == '>')
		data->err = SYNTAX_ERR_NEAR_OUTFILE;
	if (c == '<' && next_c == '<')
		data->err = SYNTAX_ERR_NEAR_HEREDOC;
	else if (c == '<')
		data->err = SYNTAX_ERR_NEAR_INFILE;
	if (c == '|')
		data->err = SYNTAX_ERR_NEAR_PIPE;
	data->is_syntax_valid = 0;
}

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
			set_syntax_error(data, s[i], s[i + 1]);
			return ;
		}
		i++;
	}
	data->is_syntax_valid = 0;
	data->err = SYNTAX_ERR_NEAR_NEWLINE;
}

void	get_pipe_err(t_data *data, char *s, int i)
{
	int	j;

	j = i - 1;
	while (j >= 0)
	{
		if (s[j] == '|')
			break ;
		if (s[j] == '<' || s[j] == '>')
		{
			data->err = SYNTAX_ERR_NEAR_PIPE;
			data->is_syntax_valid = 0;
			return ;
		}
		if (!is_space(s[j]))
			return ;
		j--;
	}
	data->is_syntax_valid = 0;
	data->err = UNEXPECTED_PIPE_TOKEN_ERR;
	ft_putstr(data->err);
	data->err = NULL;
}

void	get_err(char *err, int is_exit)
{
	size_t	i;

	i = -1;
	while (err[++i])
		write(2, &err[i], 1);
	if (is_exit)
		exit(EXIT_FAILURE);
}
