#include "../include/parsing.h"

void    close_pipes(int **pipes, int size)
{
    size_t  i;

    i = 0;
    while (pipes[i])
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
        i++;
    }
}

void    free_queue(t_queue *head)
{
    t_queue *prev;

    if (!head)
        return ;
    free_queue(head->next);
    free(head->s);
}

void    free_double_int_arr(int **arr, int size)
{
    size_t  i;

    i = 0;
    while (i < size - 1 && arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(*arr);
    *arr = NULL;
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
    free_double_char_arr(cmd->main_args);
    free_dollars(cmd->vars);
    if (cmd->heredoc_pipe[0] > 0)
        close(cmd->heredoc_pipe[0]);
    if (cmd->heredoc_pipe[1] > 0)
        close(cmd->heredoc_pipe[1]);
    free_commands(cmd->next);
    free(cmd);
}

void    destory_data(t_data **data)
{
    free_queue((*data)->heredoc);
    (*data)->heredoc = NULL;
    free_commands((*data)->commands);
    close_pipes((*data)->pipes, (*data)->n_cmds - 1);
   // free_double_int_arr((*data)->pipes, (*data)->n_cmds - 1);
    (*data)->commands = NULL;
    free(*data);
    *data = NULL;
}