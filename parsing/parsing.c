#include "../include/parsing.h"

// void    print_dollars(t_dollar *head)
// {
//     while (head)
//     {
//         printf("DOLLAR VARNAME: %s\n", head->var);
//         printf("DOLLAR VARVAL: %s\n", head->val);
//         head = head->next;
//     }
// }

// void    print_matrix(char **m)
// {
//     size_t  i;

//     i = 0;
//     while (m[i])
//     {
//         printf("Index %zu: %s\n", i, m[i]);
//         i++;
//     }
// }

// void    print_args(t_queue *head, int n)
// {
//     int i;

//     i = 1;
//     while (head)
//     {
//         printf("ARGUMENT %d cmd - %d => %s\n", i, n, head->s);
//         head = head->next;
//         i++;
//     }
// }

// void    print_cmd(t_cmd *cmd, int n)
// {
//     printf("infile - cmd %d: => %s\n", n, cmd->infile);
//     printf("outfile - cmd %d: => %s\n", n, cmd->outfile);
//     printf("cmd_name - cmd %d: %s\n", n, cmd->cmd_name);
// }

// void    print_commands(t_cmd *head)
// {
//     int i;

//     i = 0;
//     while (head)
//     {
// 	    printf("*********** COMMAND DATA *********\n");
//         print_cmd(head, i);
// 		printf("command id -> %d\n", head->cmd_id);
//         print_matrix(head->main_args);
//         printf("cmd %d line ==> %s\n", i, head->line);
//         printf("is_builtin %d: => %d\n", i, head->is_builtin);
// 		printf("\t *****-> r_end -> %d | w_end -> %d *****<-\n", head->read_end, head->write_end);
// 		printf("has_heredoc -> %d\n", head->has_heredoc);
//         head = head->next;
//         i++;
//         printf("************************************");
//     }
// }

// void    print_heredoc(t_queue *head)
// {
//     int i;

//     i = 1;
//     while (head)
//     {
//         printf("Limiter %d: %s - %p\n", i, head->s, head);
//         printf("Expand here_doc ==> %d\n", head->ex);
//         head = head->next;
//         i++;
//     }
// }

// void    is_there_any_alpha(t_data *data, char *s, int is_heredoc)
// {
//     size_t  i;

//     i = 0;
//     i += s[i] == '<';
//     while (s[i])
//     {
//         if (!is_space(s[i]) && s[i] != '|' && s[i] != '<' && s[i] != '>')
//             return ;
//         if (s[i] == '|' && is_heredoc)
//         {
//             data->err = SYNTAX_ERR_NEAR_PIPE;
//             return ;
//         }
//         if (s[i] == '<')
//         {
//             data->err = SYNTAX_ERR_NEAR_INFILE;
//             return ;
//         }
//         if (s[i] == '>' && s[i + 1] == '>')
//         {
//             data->err = SYNTAX_ERR_NEAR_OUTFILE_APPEND;
//             return ;
//         }
//         if (s[i] == '>')
//         {
//             data->err = SYNTAX_ERR_NEAR_OUTFILE;
//             return ;
//         }
//         i++;
//     }
//     data->err = SYNTAX_ERR;
// }

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
	else if (!get_inout_expression(data, cmd, s, &i))
	{
		if (!is_space(s[i] && !cmd->cmd_name))
			i += get_string(s + i, COMMAND, data, cmd);
		else if (!is_space(s[i]))
			i += get_string(s + i, ARGUMENT, data, cmd);
	}
    return (i);
}

void    parse_expression(char *s, t_data *data, t_cmd *cmd)
{
    size_t  i;
    size_t  j;
    int     place;

    i = 0;
    while (s[i] && !data->err && data->is_syntax_valid)
    {
        i += get_expression(data, cmd, s, i);
        if (data->err)
            break ;
		while (s[i] && (is_space(s[i]) || !is_token(s[i])))
			i++;
    }
    cmd->main_args = get_args(cmd);
}

void    parse_commands(t_data *data)
{
    t_cmd   *command;

    if (!data->is_syntax_valid)
    {
        printf("%s\n", data->err);
        return ;
    }
    command = data->commands;
    while (command)
    {
        command->has_heredoc = 0;
        command->is_builtin = 0;
        parse_expression(command->line, data, command);
        if (!data->is_syntax_valid)
        {
            printf("%s\n", data->err);
            break ;
        }
        command = command->next;
    }
}

t_data  *parse_line(char *s, char **env, t_env *main_env)
{
    t_data  *data;

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

/**
 * QUICK NOTE -> USE destroy_data to free all the parsing data
 * void destroy_data(t_data **data); (double pointer as an argument)
 */



int main(int ac, char **av, char **env)
{
    char    *s;
    t_data  *data;
    t_env   *main_env;

    init_env(&main_env, env);
    // t_env *k = main_env;
    // while (k)
    // {
    //     printf("%s => %s\n", k->name, k->data);
    //     k = k->next;
    // }
    while (1)
    {
        s = readline("minishell> ");
        data = NULL;
        if (s && s[0])
        {
            data = parse_line(s, env, main_env);
            if (get_queue_size(data->heredoc) > HERE_DOC_MAX)
                get_err(MAX_HERE_DOC_EXCEEDED_ERR, 1);
            // print_commands(data->commands);
            // print_heredoc(data->heredoc);
            run_heredoc(data, data->heredoc, data->commands);
            // free(s);
            // destory_data(&data);
        }
    }
}