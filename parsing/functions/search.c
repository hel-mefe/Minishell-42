/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:07:58 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:07:59 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	search_for_char(char *s, char c, char end)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != end)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	in_string(char *s, char c)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
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
