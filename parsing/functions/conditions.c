/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:35:31 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/25 23:37:06 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_token(char c)
{
	return (c == '<' || c == '|' || c == '>');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\v'
		|| c == '\r' || c == '\t' || c == '\f');
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c <= 'Z' && c >= 'A'));
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
