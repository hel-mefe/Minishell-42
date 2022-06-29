#include "parsing.h"

int get_commands_size(t_cmd *head)
{
    if (!head)
        return (0);
    return (1 + get_commands_size(head->next));
}

t_cmd   *get_command_by_id(t_cmd *head, int id)
{
    while (head)
    {
        if (head->cmd_id == id)
            return (head);
        head = head->next;
    }
    return (NULL); // NOT FOUND
}

t_cmd   *get_last_command(t_cmd *head)
{
    if (!head)
        return (NULL);
    if (!head->next)
        return (head);
    return (get_last_command(head->next));
}

t_cmd   *new_command(t_cmd *head)
{
    t_cmd   *new;

    new = (t_cmd *) malloc (sizeof(t_cmd));
    if (!new)
        return (NULL);
    new->args = NULL;
    new->infile = NULL;
    new->outfile = NULL;
    new->syntax = NULL;
    new->main_args = NULL;
    new->outfile_mode = O_CREAT;
    new->vars = NULL;
    new->cmd_name = NULL;
    new->line = NULL;
    new->is_builtin = 0;
    new->cmd_id = get_commands_size(head) + 1;
    new->error = -1;
    new->write_end = -1;
    new->read_end = -1;
    return (new);
}

void    push_command(t_cmd **head, t_cmd *new)
{
    t_cmd   *last;

    if (!(*head))
    {
        *head = new;
        new->prev = NULL;
    }
    else
    {
        last = get_last_command(*head);
        last->next = new;
        new->prev = last;
    }
    new->next = NULL;
}

size_t  get_quote_end(char *s, char c)
{
    size_t  i;
    int     end;

    end = -1;
    i = 0;
    while (s[i])
    {
        if (s[i] == c)
            end = i;
        if (s[i] == c && (!s[i + 1] || is_space(s[i + 1]) || s[i + 1] == '|'))
            break ;
        i++;
    }
    if (end == -1)
    {
        printf("QUOTES ARE NOT CLOSED PROPERLY!");
        exit(EXIT_FAILURE);
    }
    return (end);
}

t_cmd   *get_commands(char *s)
{
    size_t  i;
    size_t  j;
    t_cmd   *head;
    t_cmd   *new;
    char    *cmd;

    head = NULL;
    i = -1;
    j = 0;
    while (s[++i])
    {
        if (s[i] == '\'')
            i += get_quote_end(s + i + 1, '\'') + 1;
        else if (s[i] == '\"')
            i += get_quote_end(s + i + 1, '\"') + 1;
        if (s[i] == '|' || !s[i + 1])
        {
            new = new_command(head);
            if (!s[i + 1])
                new->line = slice(s, j, i + 1);
            else
                new->line = slice(s, j, i);
            push_command(&head, new);
            j = i + 1;
            if (s[j] == '|')
            {
                printf("UNEXPECTED PIPE TOKEN!");
                exit(EXIT_FAILURE);
            }
        }
    }
    return (head);
}
