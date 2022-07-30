/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:51:33 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:10:18 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*expand_result(t_data *data, char *res)
{
	t_dollar	*vars;
	char		*expanded;

	if (!res)
		return (NULL);
	vars = get_all_dollars(res, data->main_env);
	expanded = expand_string(vars, res);
	free_dollars(vars);
	return (expanded);
}

int	is_dollar_valid(char *s)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(s[i]))
		return (0);
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	return (1);
}

char	**get_args(t_cmd *cmd)
{
	size_t	args_size;
	size_t	i;
	char	**res;
	t_queue	*head;

	args_size = get_queue_size(cmd->args) + 1;
	res = malloc ((args_size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = ft_strdup(cmd->cmd_name);
	res[args_size] = NULL;
	head = cmd->args;
	i = 0;
	while (head && ++i < args_size)
	{
		res[i] = ft_strdup(head->s);
		head = head->next;
	}
	return (res);
}

void	alpha_except_token(t_data *data, char *s)
{
	int	i;

	i = 0;
	if (!s || !s[i])
		data->err = SYNTAX_ERR_NEAR_NEWLINE;
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

size_t	get_heredoc(char *s, t_data *data, t_cmd *cmd)
{
	size_t	i;
	int		trigger;

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
