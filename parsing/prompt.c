/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 22:51:41 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:10:26 by hel-mefe         ###   ########.fr       */
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

char	*show_prompt(void)
{
	char	*path;
	char	*input;
	char	*k_path;

	path = getcwd(NULL, 0);
	if (!path)
		path = ft_strdup("$");
	k_path = path;
	path = ft_strjoin(PATH_COLOR, path);
	if (k_path)
		free(k_path);
	k_path = path;
	path = ft_strjoin(path, INPUT_COLOR);
	if (k_path)
		free(k_path);
	input = readline(path);
	if (path)
		free(path);
	return (input);
}
