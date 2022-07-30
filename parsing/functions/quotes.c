/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:07:53 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:07:54 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	set_quote(char *c, char *si, char opposite)
{
	if (!(*c) && (*si == '\'' || *si == '\"'))
	{
		*c = *si;
		*si = BREAKING_POINT;
	}
	else if (*c && *si == *c)
	{
		if (search_for_char(si + 1, opposite, *c)
			|| (*si == '\"' && *(si + 1) == '\"'))
			*si = BREAKING_POINT;
		else if (!search_for_char(si + 1, *c, 0))
			*si = BREAKING_POINT;
		else if ((*si + 1) || is_space(*(si + 1)) || is_token(*(si + 1)))
			*si = BREAKING_POINT;
		*c = 0;
	}
}

void	set_opposite(char *c, char *opposite)
{
	if (*c == '\'')
		*opposite = '\"';
	else
		*opposite = '\'';
}

void	mark_breaking_quotes(char *s)
{
	size_t	i;
	char	c;
	char	opposite;

	c = 0;
	i = 0;
	while (s[i])
	{
		set_quote(&c, s + i, opposite);
		set_opposite(&c, &opposite);
		i++;
	}
}

char	*remove_quotes(char *s)
{
	size_t	i;
	size_t	a;
	char	*res;

	if (!s)
		return (NULL);
	res = 0;
	mark_breaking_quotes(s);
	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] == BREAKING_POINT)
		{
			res = ft_strjoin_free(res, slice(s, a, i));
			a = i + 1;
		}
		i++;
	}
	if (i > a)
		res = ft_strjoin_free(res, slice(s, a, i));
	free(s);
	return (res);
}

char	*remove_chars(char *s, char *r)
{
	size_t	i;
	size_t	j;
	char	*res;

	res = slice(s, 0, 0);
	j = 0;
	i = 0;
	while (s[i])
	{
		if (in_string(r, s[i]))
		{
			if (i != 0)
				res = ft_strjoin(res, slice(s, j, i));
			while (s[i] && in_string(r, s[i]))
				i++;
			j = i;
		}
		else
			i++;
	}
	if (i != j)
		res = ft_strjoin(res, slice(s, j, i));
	return (res);
}
