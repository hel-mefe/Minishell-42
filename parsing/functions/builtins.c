#include "../../include/parsing.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit"));
}

void	mark_builtins(t_cmd *head)
{
	while (head)
	{
		if (is_builtin(head->cmd_name))
			head->is_builtin = 1;
		head = head->next;
	}
}
