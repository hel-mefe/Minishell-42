#include "parsing.h"

void    print_dollars(t_dollar *head)
{
    while (head)
    {
        printf("DOLLAR VARNAME: %s\n", head->var);
        printf("DOLLAR VARVAL: %s\n", head->val);
        head = head->next;
    }
}

void    print_matrix(char **m)
{
    size_t  i;

    i = 0;
    while (m[i])
    {
        printf("Index %zu: %s\n", i, m[i]);
        i++;
    }
}

void    print_args(t_queue *head, int n)
{
    int i;

    i = 1;
    while (head)
    {
        printf("ARGUMENT %d cmd - %d => %s\n", i, n, head->s);
        head = head->next;
        i++;
    }
}

void    print_cmd(t_cmd *cmd, int n)
{
    printf("infile - cmd %d: => %s\n", n, cmd->infile);
    printf("outfile - cmd %d: => %s\n", n, cmd->outfile);
    printf("cmd_name - cmd %d: %s\n", n, cmd->cmd_name);
}

void    print_commands(t_cmd *head)
{
    int i;

    i = 0;
    while (head)
    {
	    printf("*********** COMMAND DATA *********\n");
        print_cmd(head, i);
		printf("command id -> %d\n", head->cmd_id);
        print_matrix(head->main_args);
        printf("cmd %d line ==> %s\n", i, head->line);
        printf("is_builtin %d: => %d\n", i, head->is_builtin);
		printf("\t *****-> r_end -> %d | w_end -> %d *****<-\n", head->read_end, head->write_end);
		printf("has_heredoc -> %d\n", head->has_heredoc);
        head = head->next;
        i++;
        printf("************************************");
    }
}

void    print_heredoc(t_queue *head)
{
    int i;

    i = 1;
    while (head)
    {
        printf("Limiter %d: %s - %p\n", i, head->s, head);
        printf("Expand here_doc ==> %d\n", head->ex);
        head = head->next;
        i++;
    }
}

void    parse_expression(char *s, t_data *data, t_cmd *cmd)
{
    size_t  i;
    int     place;
    char    *res;

    i = 0;
    while (s[i] && !cmd->syntax && cmd->error == -1 && data->is_syntax_valid)
    {
        if (s[i] == '<' && s[i + 1] == '<')
            i += get_heredoc(s + i + 2, data, cmd) + 1;
        else if (s[i] == '>' && s[i + 1] == '>' && cmd->error == -1)
        {
            cmd->outfile_mode = O_APPEND;
            i += get_string(s + i + 2, OUTFILE, data, cmd) + 1;
        }
        else if (s[i] == '<' && cmd->error == -1)
            i += get_string(s + i + 1, INFILE, data, cmd);
        else if (s[i] == '>' && cmd->error == -1)
        {
            cmd->outfile_mode = O_CREAT;
            i += get_string(s + i + 1, OUTFILE, data, cmd);
        }
        else if (!is_space(s[i]) && !cmd->cmd_name)
            i += get_string(s + i, COMMAND, data, cmd);
        else if (!is_space(s[i]))
            i += get_string(s + i, ARGUMENT, data, cmd);
        if (s[i] == '|')
        {
            cmd->error = 0;
            data->is_syntax_valid = 0;
        }
		if (!is_token(s[i]))
			i++;
    }
    cmd->main_args = get_args(cmd);
    free_queue(cmd->args);
}

void    parse_commands(t_data *data)
{
    t_cmd   *command;

    command = data->commands;
    while (command)
    {
        command->has_heredoc = 0;
        parse_expression(command->line, data, command);
        command = command->next;
    }
}

void    prepare_data(t_data *data)
{
    int     i;
    t_cmd   *cmd;

    data->pipes = (int **) malloc (data->n_cmds * sizeof(int *));
    cmd = data->commands;
    i = 0;
    while (i < data->n_cmds)
    {
        if (cmd->syntax)
            data->is_syntax_valid = 1;
        data->pipes[i] = (int *) malloc (2 * sizeof(int));
        pipe(data->pipes[i]);
        if (i == 0 && cmd->read_end == -1)
            cmd->read_end = 0;
        else if (cmd->has_heredoc)
            cmd->read_end = data->pipes[i][0];
        else if (cmd->read_end == -1)
            cmd->read_end = data->pipes[i - 1][0];
        if (i == data->n_cmds - 1 && cmd->write_end == -1)
            cmd->write_end = 1;
        else if (cmd->write_end == -1)
            cmd->write_end = data->pipes[i][1];
        cmd = cmd->next;
        i++;
    }
}

t_data  *parse_line(char *s, char **env)
{
    t_data  *data;

    data = (t_data *) malloc (sizeof(t_data));
    if (!data)
        return (NULL);
    data->commands = get_commands(s);
    data->heredoc = NULL;
    data->env = env;
    data->is_syntax_valid = 1;
    parse_commands(data);
    mark_builtins(data->commands);
    data->n_cmds = get_commands_size(data->commands);
    prepare_data(data);
    return (data);
} 
