#include "../include/parsing.h"

int ft_strncmp(char *s1, char *s2, size_t n)
{
    size_t  i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (i < n && (s1[i] || s2[i]))
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (0);
}

int ft_strcmp(const char *s1, const char *s2)
{
    int i;

    if (!s1 || !s2)
        return (0);
    i = 0;
    while (s1[i] || s2[i])
    {
        if (s1[i] == '\n' && !s2[i])
            return (0);
        if (s2[i] == '\n' && s1[i])
            return (0);
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (0);
}

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

int is_token(char c)
{
    return (c == '<' || c == '|' || c == '>');
}

int is_space(char c)
{
    return (c == ' ' || c == '\n' || c == '\v' || c == '\r' || c == '\t' || c == '\f');
}

int ft_isalpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c <= 'Z' && c >= 'A'));
}

int ft_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

int ft_isalnum(char c)
{
    return (ft_isalpha(c) || ft_isdigit(c));
}

char    **get_args(t_cmd *cmd)
{
    size_t  args_size;
    size_t  i;
    char    **res;
    t_queue *head;

    args_size = get_queue_size(cmd->args) + 1;
    // printf("ARGS_SIZE => %zu\n", args_size);
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

t_dollar    *new_dollar(char *var, char *val)
{
    t_dollar    *new;

    new = (t_dollar *) malloc (sizeof(t_dollar));
    if (!new)
        return (NULL);
    new->var = var;
    new->val = val;
    return (new);
}

t_dollar    *get_last_dollar(t_dollar *head)
{
    if (!head)
        return (NULL);
    if (!head->next)
        return (head);
    return (get_last_dollar(head->next));
}

void    push_back_dollar(t_dollar **head, t_dollar *new)
{
    t_dollar    *last;

    if (!(*head))
        *head = new;
    else
    {
        last = get_last_dollar(*head);
        last->next = new;
    }
    new->next = NULL;
}