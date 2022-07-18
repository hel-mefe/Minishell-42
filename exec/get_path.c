/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:59:25 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/18 18:21:51 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

char	*get_command(t_env **path, char *cmd)
{
	char	**tmp;
	char	*tab;
	char	*command;
	int		i;
	t_env   *new;

	i = 0;

	if (!cmd)
		return (NULL);
	if (check_path(cmd))
		return (cmd);
	if (cmd[0] == '/')
		ft_error1(-1, "No such file or directory\n");
	new = search_element(path, "PATH");
	if (new == NULL)
		ft_error1(-1, "no such file or directory\n");
	tmp = ft_split(new->data, ':');
	while (tmp[i])
	{
		tab = ft_strjoin(tmp[i], "/");
		command = ft_strjoin(tab, cmd);
		free(tab);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (NULL);
}
