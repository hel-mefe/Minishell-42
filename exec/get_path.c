/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:59:25 by ytijani           #+#    #+#             */
/*   Updated: 2022/06/29 20:43:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_path(char *cmd)
{
	char	*command;

	command = cmd;
	if (access(command, X_OK) == 0)
		return (1);
	else
		return (0);
}

void	ft_error1(int code, char *str)
{
	if (code < 0)
	{
		ft_putstr_fd(str, 2);
		exit(1);
	}
}

char	*get_path(char **path)
{
	while (ft_strncmp("PATH=", *path, 5))
		path++;
	return (*path + 5);
}

char	*get_command(t_env **path, char *cmd)
{
	char	**tmp;
	char	*tab;
	char	*command;
	int		i;
	t_env   *new;

	i = 0;
	if (!*cmd)
		ft_error1(-1, "command not found\n");
	new = search_element(path, "PATH");
	tmp = ft_split(new->data, ':');
	while (tmp[i])
	{
		tab = ft_strjoin(tmp[i], "/");
		command = ft_strjoin(tab, cmd);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}
