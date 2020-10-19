/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parcer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:18:18 by jheat             #+#    #+#             */
/*   Updated: 2020/10/19 16:18:18 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char		**make_map(t_all *all)
{
	char		**map;
	int			i;
	int			size;
	t_list		*tmp;

	size = ft_lstsize(all->head);
	map = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	tmp = all->head;
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	map[++i] = NULL;
	return (map);
}
