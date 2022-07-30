/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:09:00 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:09:01 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_dollar_char_valid(char c)
{
	return (!is_space(c) && (ft_isalnum(c) || c == '_'));
}

char	*get_dollar(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && is_dollar_char_valid(s[i]))
		i++;
	return (slice(s, 0, i));
}

t_dollar	*get_all_dollars(char *s, t_env *main_env)
{
	size_t		i;
	t_dollar	*new;
	t_dollar	*head;
	char		*dollar;

	i = 0;
	head = NULL;
	while (s[i])
	{
		if (s[i] == '$' && is_dollar_valid(s + i + 1))
		{
			dollar = get_dollar(s + i + 1);
			i += ft_strlen(dollar);
			new = new_dollar(dollar, get_dollar_val(dollar, main_env));
			push_back_dollar(&head, new);
		}
		else
			i++;
	}
	return (head);
}

char	*get_dollar_val(char *var, t_env *main_env)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(var);
	i = 0;
	while (main_env)
	{
		if (!ft_strcmp(var, main_env->name))
			return (ft_strdup(main_env->data));
		main_env = main_env->next;
	}
	return (slice(var, 0, 0));
}
