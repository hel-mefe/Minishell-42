/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:08:02 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:08:03 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	ft_putstr(char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		write(1, &s[i], 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*res;

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

char	*slice(char *s, size_t a, size_t b)
{
	char	*res;
	size_t	len;
	size_t	i;

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
