/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:51:37 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:10:23 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	get_inout_expression(t_data *data, t_cmd *cmd, char *s, size_t *i)
{
	int		trigger;
	size_t	j;

	j = *i;
	trigger = 0;
	if (s[j] == '<')
	{
		catch_syntax_err(data, s + j + 1);
		if (!data->err)
			*i += get_string(s + j + 1, INFILE, data, cmd) + 1;
		trigger = 1;
	}
	else if (s[j] == '>')
	{
		catch_syntax_err(data, s + j + 1);
		if (!data->err)
			*i += get_string(s + j + 1, OUTFILE, data, cmd) + 1;
		trigger = 1;
	}
	return (trigger);
}

size_t	get_expression(t_data *data, t_cmd *cmd, char *s, size_t i)
{
	if (s[i] == '<' && s[i + 1] == '<')
		i += get_heredoc(s + i + 2, data, cmd) + 2;
	else if (s[i] == '>' && s[i + 1] == '>')
	{
		cmd->outfile_mode = O_APPEND;
		catch_syntax_err(data, s + i + 2);
		if (!data->err)
			i += get_string(s + i + 2, OUTFILE, data, cmd) + 2;
	}
	else if (!get_inout_expression(data, cmd, s, &i) && !data->err)
	{
		if (!is_space(s[i]) && !cmd->cmd_name)
			i += get_string(s + i, COMMAND, data, cmd);
		else if (!is_space(s[i]))
			i += get_string(s + i, ARGUMENT, data, cmd);
	}
	return (i);
}

void	parse_expression(char *s, t_data *data, t_cmd *cmd)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	while (i < len && s[i] && !data->err && data->is_syntax_valid)
	{
		i = get_expression(data, cmd, s, i);
		if (data->err || !data->is_syntax_valid)
			break ;
		while (i < len && s[i] && is_space(s[i]))
			i++;
	}
	cmd->main_args = get_args(cmd);
}

void	parse_commands(t_data *data)
{
	t_cmd	*command;

	command = data->commands;
	while (command)
	{
		command->has_heredoc = 0;
		command->is_builtin = 0;
		parse_expression(command->line, data, command);
		if (!data->is_syntax_valid)
			break ;
		command = command->next;
	}
}

t_data	*parse_line(char *s, char **env, t_env *main_env)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof(t_data));
	if (!data)
		return (NULL);
	data->heredoc = NULL;
	data->env = env;
	data->is_syntax_valid = 1;
	data->pipes = NULL;
	data->main_env = main_env;
	data->err = NULL;
	data->commands = get_commands(data, s);
	parse_commands(data);
	mark_builtins(data->commands);
	data->n_cmds = get_commands_size(data->commands);
	prepare_data(data);
	return (data);
}

// int main(int ac, char **av, char **env)
// {
//     char    *s;
//     t_data  *data;
//     t_env   *main_env;

//     init_env(&main_env, env);
//     // t_env *k = main_env;
//     // while (k)
//     // {
//     //     printf("%s => %s\n", k->name, k->data);
//     //     k = k->next;
//     // }
//     while (1)
//     {
//         s = readline("minishell> ");
//         data = NULL;
//         if (s && s[0])
//         {
//             data = parse_line(s, env, main_env);
//             if (get_queue_size(data->heredoc) > HERE_DOC_MAX)
//                 get_err(MAX_HERE_DOC_EXCEEDED_ERR, 1);
//             print_commands(data->commands);
//             print_heredoc(data->heredoc);
//             run_heredoc(data, data->heredoc, data->commands);
//             // free(s);
//             // destory_data(&data);
//         }
//     }
// }
