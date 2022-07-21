/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:59:25 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/21 20:23:01 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

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
		exit(127);
	}
}

char	*check_access(char **tmp, char *tab, char *cmd, int i)
{
	char	*command;

	tab = ft_strjoin(tmp[i], "/");
	command = ft_strjoin(tab, cmd);
	free(tab);
	if (access(command, X_OK) == 0)
		return (command);
	free(command);
	free(tmp[i]);
	return (NULL);
}

char	*get_command(t_env **path, char *cmd)
{
	char	**tmp;
	char	*tab;
	char	*command;
	int		i;
	t_env	*new;

	i = 0;
	if (!cmd)
		exit(0);
	if (check_path(cmd))
		return (cmd);
	if (cmd[0] == '/')
		ft_error1(-1, "no such file or directory\n");
	new = search_element(path, "PATH");
	if (new == NULL)
		ft_error1(-1, "no such file or directory\n");
	tmp = ft_split(new->data, ':');
	while (tmp[i])
	{
		if (check_access(tmp, tab, cmd, i))
			return (check_access(tmp, tab, cmd, i));
		i++;
	}
	free(tmp);
	return (NULL);
}
