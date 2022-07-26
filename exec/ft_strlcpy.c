/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:33:33 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/19 17:43:44 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (src[i] != '\0')
		i++;
	if (dstsize == '\0')
		return (i);
	while (src[c] != '\0' && c < dstsize - 1)
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = '\0';
	return (i);
}
