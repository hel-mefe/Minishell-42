/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 23:11:01 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/26 10:07:33 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	*expand_string(t_dollar *dollars, char **env, int *place, char *s)
{
	size_t	i;
	size_t	j;
	char	*res;
	char	*part;
	char	*k_res;
	int		singly;
	int		doubly;

	doubly = 0;
	singly = 0;
	res = NULL;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !doubly)
			singly = !singly;
		if (s[i] == '\"' && !singly)
			doubly = !doubly;
		if (s[i] == '$' && ft_isdigit(s[i + 1]) && !singly)
        {
            k_res = res;
            part = slice(s, j, i);
            res = ft_strjoin_free(res, part);
            i += 1;
            j = i + 1;
        }
        else if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_') && !singly)
        {
            if (j != i)
            {
                k_res = part;
                part = slice(s, j, i);
                res = ft_strjoin_free(res, part);
            }
            k_res = res;
            res = ft_strjoin(res, dollars->val);
            i += ft_strlen(dollars->var);
            j = i + 1;
            dollars = dollars->next;
            if (k_res)
                free(k_res);
        }
		else if (s[i] == '$' && s[i + 1] == '?' && !singly)
		{
			if (j != i)
			{
				k_res = res;
				part = slice(s, j, i);
				res = ft_strjoin_free(res, part);
            }
			part = ft_itoa(g_global.get_nb_status);
			res = ft_strjoin_free(res, part);
			i += 1;
			j = i + 1;
		}
		i++;
	}
	if (i != j)
	{
		part = slice(s, j, i);
		res = ft_strjoin_free(res, part);
	}
	return (res);
}
