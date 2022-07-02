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
    while (s[i])
    {
        if (s[i] == '<' && s[i + 1] == '<')
            i += get_heredoc(s + i + 2, data, cmd) + 1;
        else if (s[i] == '>' && s[i + 1] == '>')
        {
            cmd->outfile_mode = O_APPEND;
            i += get_string(s + i + 2, OUTFILE, data, cmd) + 2;
            if (i > ft_strlen(s))
                break ;
        }
        else if (s[i] == '<')
            i += get_string(s + i + 1, INFILE, data, cmd) + 1;
        else if (s[i] == '>')
        {
            cmd->outfile_mode = O_CREAT;
            i += get_string(s + i + 1, OUTFILE, data, cmd) + 1;
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
        // if (i >= ft_strlen(s))
        //     break ;
		if (s[i] && is_space(s[i]))
			i++;
        printf("%zu - %s\n", i, s + i);
    }
    printf("%zu\n", i);
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

/**
 * When there is an infile or heredoc, cmd->read_end != -1
 * If there is no infile the read_end == -1
 * If there is a heredoc the command reads from ITS OWN PIPE!
 * If there is no heredoc then the command reads for (cmd - 1 PIPE (read_end) )!
 */
char    *get_heredoc_name(int cmd_id)
{
    char    *name;

    name = ft_strjoin(HERE_DOC_NAME, ft_itoa(cmd_id * 1337));
    name = ft_strjoin("/tmp/", name);
    printf("NAME: %s\n", name);
    return (name);
}

void    prepare_data(t_data *data)
{
    int     i;
    t_cmd   *cmd;


    data->pipes = (int **) malloc ((data->n_cmds - 1) * sizeof(int *));
    cmd = data->commands;
    i = 0;
    while (i < data->n_cmds)
    {
        if (i < data->n_cmds - 1)
        {
            data->pipes[i] = (int *) malloc(2 * sizeof(int));
            pipe(data->pipes[i]);
        }
        if (cmd->write_end == -1) // if there is no infile
        {
            if (i == data->n_cmds - 1)
                cmd->write_end = 1;
            else
                cmd->write_end = data->pipes[i][1];
        }                
        if (cmd->read_end == -1) // if there is no outfile
        {
            if (i == 0 && !cmd->has_heredoc)
                cmd->read_end = 0;
            else if (cmd->has_heredoc)
            {
                cmd->read_end = cmd->heredoc_pipe[0];
                pipe(cmd->heredoc_pipe);
            }
            else
                cmd->read_end = data->pipes[i - 1][0];
        }
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

// int main(int ac, char **av, char **env)
// {
//     char    *s;
//     t_data  *data;

//     while (1)
//     {
//         s = readline("minishell> ");
//         data = parse_line(s, env);
//         if (get_queue_size(data->heredoc) > HERE_DOC_MAX)
//             get_err(MAX_HERE_DOC_EXCEEDED_ERR, 1);
//         print_commands(data->commands);
//         print_heredoc(data->heredoc);
//         run_heredoc(data, data->heredoc, data->commands);
//     }
// }