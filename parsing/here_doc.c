#include "../include/parsing.h"

t_heredoc   *new_heredoc(void)
{
    t_heredoc   *new;

    new = (t_heredoc *) malloc (sizeof(t_heredoc));
    if (!new)
        return (NULL);
    new->limiters = NULL;
    return (new);
}

t_heredoc   *get_last_heredoc(t_heredoc *head)
{
    if (!head)
        return (NULL);
    if (!head->next)
        return (head);
    return (get_last_heredoc(head->next));
}

void    push_heredoc_back(t_heredoc **head, t_heredoc *new)
{
	t_heredoc   *last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_heredoc(*head);
		last->next = new;
	}
	new->next = NULL;
}

size_t	get_queue_size(t_queue *head)
{
	if (!head)
		return (0);
	return (get_queue_size(head->next) + 1);
}

t_queue *new_queue_node(char *s)
{
    t_queue *new;

    new = (t_queue *) malloc (sizeof(t_queue));
    if (!new)
        return (NULL);
    new->s = s;
    return (new);
}

t_queue *get_last(t_queue *head)
{
    if (!head)
        return (NULL);
    if (!head->next)
        return (head);
    return (get_last(head->next));
}

void    push_back(t_queue **head, t_queue *new)
{
    t_queue *last;

    if (!(*head))
        *head = new;
    else
    {
        last = get_last(*head);
        last->next = new;
    }
    new->next = NULL;
}

size_t  get_heredoc(char *s, t_data *data, t_cmd *cmd)
{
    size_t  i;
    int     trigger;

    trigger = 0;
    i = 0;
    is_there_any_alpha(data, s + i, 1);
    if (data->err)
        return (i);
    while (s[i])
    {
        while (is_space(s[i]))
            i++;
        if (s[i] == '<' && s[i + 1] == '<' && trigger)
            i += 2;
        is_there_any_alpha(data, s + i, 1);
        if (data->err)
            break ;
        else if (trigger)
            return (i);
        i += get_string(s + i, HERE_DOC, data, cmd);
        trigger = 1;
    }
    return (i);
}