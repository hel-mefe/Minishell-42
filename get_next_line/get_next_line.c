/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:30:00 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/26 17:25:46 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

int	in_buffer(char	*save)
{
	int	i;

	i = 0;
	if (!save)
		return (0);
	while (save[i])
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_puts(char *save, int fd)
{
	char	*buffer;
	int		size;

	size = 1;
	if (in_buffer(save))
		return (save);
	buffer = (char *) malloc(sizeof(char) * (1 + 1));
	if (buffer == 0)
		return (0);
	while (!in_buffer(save) && size)
	{
		size = read(fd, buffer, 1);
		if (size == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[size] = '\0';
		save = ft_strjoins(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*ft_line(char	*save)
{
	int		i;
	char	*line;
	int		j;

	i = 0;
	j = 0;
	if (!save[0])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (i > j)
	{
		line[j] = save[j];
		j++;
	}
	if (save[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*ft_sub_line(char *save)
{
	int		i;
	char	*linesub;
	int		len;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(save);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	linesub = malloc(sizeof(char) * (len - i + 1));
	if (!linesub)
		return (NULL);
	i += 1;
	while (len > i)
		linesub[j++] = save[i++];
	linesub[j] = '\0';
	free(save);
	return (linesub);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if ((fd < 0 || fd >= 1024) || read(fd, save, 0) < 0)
		return (NULL);
	save = ft_puts(save, fd);
	if (!save)
		return (NULL);
	line = ft_line(save);
	if (!line)
		return (NULL);
	save = ft_sub_line(save);
	return (line);
}
