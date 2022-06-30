#include "parsing.h"

void    close_pipes(int **pipes, int size)
{
    size_t  i;

    i = 0;
    while (i < size)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

void    free_queue(t_queue *head)
{
    t_queue *prev;

    while (head)
    {
        prev = head;
        head = head->next;
        free(prev->s);
        free(prev);
    }
}

void    free_double_int_arr(int **arr)
{
    size_t  i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void    free_double_char_arr(char **arr)
{
    size_t  i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void    free_dollars(t_dollar *head)
{
    t_dollar    *prev;

    while (head)
    {
        prev = head;
        head = head->next;
        free(prev->var);
        free(prev->val);
        free(prev);
    }
}

void    free_commands(t_cmd *cmd)
{
    if (!cmd)
        return ;
    free(cmd->line);
    free(cmd->cmd_name);
    free(cmd->infile);
    free(cmd->outfile);
    free_queue(cmd->args);
    free_double_char_arr(cmd->env);
    free_double_char_arr(cmd->main_args);
    free_dollars(cmd->vars);
    free_commands(cmd->next);
    free(cmd);
}

void    destory_data(t_data **data)
{
    free_queue((*data)->heredoc);
    free_commands((*data)->commands);
    close_pipes((*data)->pipes, (*data)->n_cmds - 1);
    free_double_int_arr((*data)->pipes);
    *data = NULL;
}