#include "parsing.h"

int is_dollar_valid(char *s)
{
    size_t  i;

    i = 0;
    if (ft_isdigit(s[i]))
        return (0);
    if (!ft_isalpha(s[i]) && s[i] != '_')
        return (0);
    return (1);
}

char    **get_args(t_cmd *cmd)
{
    size_t  args_size;
    size_t  i;
    char    **res;
    t_queue *head;

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