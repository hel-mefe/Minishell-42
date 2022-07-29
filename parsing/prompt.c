/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:51:41 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/29 22:51:42 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	*get_prompt_path(t_env *head)
{
	while (head)
	{
		if (!ft_strcmp(head->name, "PWD"))
			return (ft_strdup(head->data));
		head = head->next;
	}
	return (NULL);
}

char	*show_prompt(t_env *head)
{
	char	*path;
	char	*input;
	size_t	i;

	path = get_prompt_path(head);
	i = -1;
	while (PATH_COLOR[++i])
		write(1, &PATH_COLOR[i], 1);
	ft_putstr(path);
	free(path);
	input = readline(INPUT_COLOR"\n🧬 ➡️ ");
	return (input);
}
