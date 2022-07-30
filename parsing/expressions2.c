/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expressions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:51:07 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:10:06 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*get_normal_string(char *s)
{
	size_t	i;
	char	*res;
	int		singly;
	int		doubly;

	singly = 0;
	doubly = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !doubly)
			singly = !singly;
		if (s[i] == '\"' && !singly)
			doubly = !doubly;
		if (is_token(s[i]) && !doubly && !singly)
			break ;
		if (is_space(s[i]) && !doubly && !singly)
			break ;
		i++;
	}
	res = slice(s, 0, i);
	return (res);
}

char	*get_singly_string(char *s)
{
	size_t	i;
	char	*res;
	int		valid;

	valid = 0;
	i = 0;
	if (s[i] == '\'')
		i += 1;
	while (s[i])
	{
		if (s[i] == '\'')
			valid = !valid;
		if (s[i] == '\'' && (!s[i + 1] || is_space(s[i + 1])))
			break ;
		i++;
	}
	if (!s[i])
		res = slice(s, 0, i);
	else
		res = slice(s, 0, i + 1);
	return (res);
}

char	*get_doubly_string(char *s)
{
	size_t	i;
	char	*res;
	int		valid;

	valid = 0;
	i = 0;
	if (s[i] == '\"')
		i += 1;
	while (s[i])
	{
		if (s[i] == '\"')
			valid = !valid;
		if ((s[i] == '\"' && (is_space(s[i + 1]) || !s[i + 1])))
			break ;
		i++;
	}
	if (!s[i])
		res = slice(s, 0, i);
	else
		res = slice(s, 0, i + 1);
	return (res);
}
