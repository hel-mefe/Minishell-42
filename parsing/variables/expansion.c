/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:08:43 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:08:44 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	init_expansion_vars(size_t *ij, char **res, int *singly_doubly)
{
	ij[0] = 0;
	ij[1] = 0;
	*res = NULL;
	singly_doubly[0] = 0;
	singly_doubly[1] = 0;
}

char	*status_dollar(char *s, char *old_res, size_t *ij)
{
	char	*res;

	res = old_res;
	if (ij[0] != ij[1])
		res = j_different_than_i(s, res, ij[1], ij[0]);
	res = get_status(res, &ij[1], &ij[0]);
	return (res);
}

char	*valid_dollar(char *s, char *old_res, size_t *ij, t_dollar **dollars)
{
	char	*res;

	res = old_res;
	if (ij[0] != ij[1])
		res = j_different_than_i(s, res, ij[1], ij[0]);
	res = add_variable(&ij[1], &ij[0], res, dollars);
	return (res);
}

char	*expand_string(t_dollar *dollars, char *s)
{
	size_t	ij[2];
	char	*res;
	int		singly_doubly[2];

	init_expansion_vars(ij, &res, singly_doubly);
	while (s[ij[1]])
	{
		set_quotes(s[ij[1]], &singly_doubly[0], &singly_doubly[1]);
		if (s[ij[1]] == '$' && ft_isdigit(s[ij[1] + 1]) && !singly_doubly[0])
			res = digit_after_dollar(s, res, &ij[1], &ij[0]);
		else if (s[ij[1]] == '$' && (ft_isalpha(s[ij[1] + 1]) \
		|| s[ij[1] + 1] == '_') && !singly_doubly[0])
			res = valid_dollar(s, res, ij, &dollars);
		else if (s[ij[1]] == '$' && s[ij[1] + 1] == '?' && !singly_doubly[0])
			res = status_dollar(s, res, ij);
		ij[1]++;
	}
	if (ij[1] != ij[0])
		res = j_different_than_i(s, res, ij[1], ij[0]);
	return (res);
}
