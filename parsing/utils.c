#include "parsing.h"

int     is_builtin(char *cmd)
{
    return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "cd") \
            || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") \
            || !ft_strcmp(cmd, "exit"));
}
void    mark_builtins(t_cmd *head)
{
    while (head)
    {
        if (is_builtin(head->cmd_name))
            head->is_builtin = 1;
        head = head->next;
    }
}

size_t  ft_strlen(const char *s)
{
    size_t  i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}

char    *ft_strdup(const char *s)
{
    size_t  len;
    size_t  i;
    char    *res;

    if (!s)
        return (NULL);
    len = ft_strlen(s);
    res = (char *) malloc ((len + 1) * sizeof(char));
    if (!res)
        return (NULL);
    i = -1;
    while (++i < len)
        res[i] = s[i];
    res[i] = 0;
    return (res);
}

char    *slice(char *s, size_t a, size_t b)
{
    char    *res;
    size_t  len;
    size_t  i;

    len = b - a;
    if (len < 0)
        return (NULL);
    res = (char *) malloc ((len + 1) * sizeof(char));
    if (!res)
        return (NULL);
    i = -1;
    while (++i < len && a < b)
        res[i] = s[a++];
    res[i] = 0;
    return (res);
}

char    *expand_expression(char *res)
{
    return (res);
}

char    *get_normal_string(char *s, t_cmd *cmd)
{
    size_t  i;
    char    *res;

    i = 0;
    while (s[i] && !is_space(s[i]) && !is_token(s[i]))
        i++;
    res = slice(s, 0, i);
    return (res);
}

void    assign_string(char *s, int place, t_data *data, t_cmd *cmd)
{
    t_queue *new;

    if (place == INFILE)
    {
        if (cmd->infile)
            free(cmd->infile);
        cmd->infile = s;
        cmd->read_end = open(cmd->infile, O_RDONLY);
        if (cmd->read_end < 0)
            cmd->error = errno;
        cmd->has_heredoc = 0;
    }
    else if (place == COMMAND)
        cmd->cmd_name = s;
    else if (place == OUTFILE)
    {
        if (cmd->outfile)
            free(cmd->outfile);
        cmd->outfile = s;
        if (cmd->outfile_mode == O_APPEND)
            cmd->write_end = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            cmd->write_end = open(cmd->outfile, O_WRONLY | O_CREAT, 0644);
        if (cmd->write_end < 0)
            cmd->error = errno;
    }
    else if (place == HERE_DOC || place == EXPANDED_HERE_DOC)
    {
        cmd->has_heredoc = 1;            
        new = new_queue_node(s);
        new->ex = 0;
        if (place == EXPANDED_HERE_DOC)
            new->ex = 1;
        new->cmd_id = cmd->cmd_id;
        push_back(&data->heredoc, new);
    }
    else if (place == ARGUMENT)
    {
        new = new_queue_node(s);
        push_back(&cmd->args, new);
    }
    return ;
}

char    *get_singly_string(char *s, t_cmd *cmd)
{
    size_t  i;
    char    *res;
    int     valid;

    valid = 0;
    i = 0;
    if (s[i] == '\'')
        i += 1;
    while (s[i])
    {
        if (s[i] == '\'')
            valid = !valid;
        if (s[i] == '\'' && (!s[i + 1] || is_space(s[i + 1])))
            break ;
        i++;
    }
    if (!valid)
        printf("INVALID SINGLY\n");
    if (!s[i])
        res = slice(s, 0, i);
    else
        res = slice(s, 0, i + 1);
    return (res);
}
char    *get_doubly_string(char *s, t_cmd *cmd)
{
    size_t  i;
    char    *res;
    int     valid;

    valid = 0;
    i = 0;
    if (s[i] == '\"')
        i += 1;
    while (s[i])
    {
        if (s[i] == '\"')
            valid = !valid;
        if ((s[i] == '\"' && (is_space(s[i + 1]) || !s[i + 1])))
            break ;
        i++;
    }
    if (!valid)
        printf("INVALID DOUBLY\n");
    if (!s[i])
        res = slice(s, 0, i);
    else
        res = slice(s, 0, i + 1);
    return (res);
}

size_t  get_string(char *s, int place, t_data *data, t_cmd *cmd)
{
    size_t  i;
    char    *res;
    char    *expanded_res;
    t_dollar    *dollars;

    i = 0;
    while (s[i] && is_space(s[i]))
        i++;
    if (s[i] == '\"')
        res = get_doubly_string(s + i, cmd);
    else if (s[i] == '\'')
        res = get_singly_string(s + i, cmd);
    else
        res = get_normal_string(s + i, cmd);
    i += ft_strlen(res);
    if (s[i] != '\'' && place != HERE_DOC)
    {
        dollars = get_all_dollars(s, data->env);
        expanded_res = expand_string(dollars, data->env, &place, res);
    }
    else
        expanded_res = res;
    expanded_res = remove_quotes(ft_strdup(expanded_res));
    if (ft_strlen(expanded_res) == ft_strlen(res) && place == HERE_DOC)
        place = EXPANDED_HERE_DOC;
    assign_string(expanded_res, place, data, cmd);
    return (i);
}