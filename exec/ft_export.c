/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:26:28 by marvin            #+#    #+#             */
/*   Updated: 2022/06/26 19:39:42 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_sort(t_env **env_v)
{
	t_env	*tmp;
	int		size;
	char	*swap;

	size = ft_lstsize(*env_v);
	while (size)
	{
		tmp = (*env_v);
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				swap = tmp->name;
				tmp->name = tmp->next->name;
				tmp->next->name = swap;
				swap = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = swap;
			}
			tmp = tmp->next;
		}
		size--;
	}
}

void	print_export(t_env **env_v)
{
	t_env *new;

	ft_sort(env_v);
	new = *env_v;
	while(new)
	{
		printf("declare -x %s",new->name);
		printf("=\"");
		printf("%s",new->data);
		printf("\"\n");
		new = new->next;
	}
}

void	ft_export(t_env **env_v, char **av)
{
	int i;
	char **spl;
	t_env *new;

	i = 0;
	if (av[i + 1] == '\0')
		print_export(env_v);
	else if (av[i + 1] != '\0')
	{
		while (av[i])
		{
			if ((ft_strchr(av[i], '=')) == 1)
			{
				spl = ft_split(av[i], '=');
				if (spl[1] != NULL)
					new = ft_lstnew(spl[0], spl[1]);
				ft_lstadd_back(env_v, new);
			}
			i++;
		}
	} 
}
