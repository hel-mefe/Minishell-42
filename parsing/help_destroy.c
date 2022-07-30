/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:10:11 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:10:13 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	close_pipes(int **pipes, int size)
{
	int	i;

	i = 0;
	while (i < size && pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
}

void	free_queue(t_queue *head)
{
	if (!head)
		return ;
	free_queue(head->next);
	free(head->s);
	free(head);
}

void	free_double_int_arr(int **arr, int size)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < size - 1 && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_double_char_arr(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_dollars(t_dollar *head)
{
	t_dollar	*prev;

	while (head)
	{
		prev = head;
		head = head->next;
		free(prev->var);
		free(prev->val);
		free(prev);
	}
}
