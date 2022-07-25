/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:05:05 by hel-mefe          #+#    #+#             */
/*   Updated: 2021/12/01 15:10:57 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


void	ft_bzero(char *s, unsigned int start, size_t len)
{
	unsigned char	*str;
	unsigned char	c;

	str = (unsigned char *) s;
	c = 0;
	while (start < len)
	{
		str[start] = c;
		start++;
	}
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	if (start > len || start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	res = (char *) malloc ((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = 0;
	return (res);
}
