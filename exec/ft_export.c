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
		if (new->data != NULL)
		{
			printf("=\"");
			printf("%s",new->data);
			printf("\"");
		}
		printf("\n");
		new = new->next;
	}
}

void	check_evr(t_env **env_v, char **spl)
{
	int index;
	t_env *new;

	new = *env_v;
	new = search_element(env_v, spl[0]);
	// index = get_myid(env_v, spl[0]);
	// printf("my spl[0]-->%s\n", spl[0]);
	if (new != NULL)
	{
		free(new->data);
		new->data = spl[1];
	}
	else
		{
		new = ft_lstnew(spl[0], spl[1]);
		ft_lstadd_back(env_v, new);
		}
}

void	ft_export(t_env **env_v, char **av)
{
	int i;
	char *spl[2];
	char *sig;
	t_env *new;

	i = 0;
	if (av[i + 1] == '\0')
		print_export(env_v);
	else if (av[i + 1] != '\0')
	{
		while (av[i])
		{
			sig = strstr(av[i], "=");
			if (sig)
			{
				spl[1] = strdup(sig + 1);
				spl[0] = *ft_split(av[i], '=');
				if (spl[1] != NULL)
					check_evr(env_v, spl);
			}
			i++;
		}
	} 
	get_nb_status = 0;
}
