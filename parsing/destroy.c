#include "../include/parsing.h"

void    close_pipes(int **pipes, int size)
{
    size_t  i;

    i = 0;
    while (i < size && pipes[i])
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
    free(head);
}

void    free_double_int_arr(int **arr, int size)
{
    size_t  i;

    i = 0;
    if (!arr)
        return ;
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
    if (!arr)
        return ;
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

void    free_str(char **ptr)
{
    if (*ptr)
        free(*ptr);
    *ptr = NULL;
}

void    free_commands(t_cmd *cmd)
{
    if (!cmd)
        return ;
    free_str(&cmd->line);
    free_str(&cmd->cmd_name);
    free_str(&cmd->infile);
    free_str(&cmd->outfile);
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
   free((*data)->pipes);
    (*data)->commands = NULL;
    free(*data);
    *data = NULL;
}