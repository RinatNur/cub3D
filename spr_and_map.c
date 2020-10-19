/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_and_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:01:46 by jheat             #+#    #+#             */
/*   Updated: 2020/10/19 17:21:55 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double			ft_plr_vision(char map_vision)
{
	if (map_vision == 'N')
		return (3 * M_PI / 2);
	else if (map_vision == 'S')
		return (M_PI / 2);
	else if (map_vision == 'E')
		return (0);
	else if (map_vision == 'W')
		return (M_PI);
	return (0);
}

t_spr_list		*ft_spr_lstnew(int x, int y, int len)
{
	t_spr_list		*new_el;

	if (!(new_el = malloc(sizeof(t_spr_list))))
		exit_err("Malloc: memory is not allocated", 33);
	new_el->spr_x = x;
	new_el->spr_y = y;
	new_el->len_from_plr = len;
	new_el->next = NULL;
	return (new_el);
}

void			ft_spr_lstadd_back(t_spr_list **lst, t_spr_list *new)
{
	t_spr_list		*last;

	last = *lst;
	if (!last)
		*lst = new;
	else if (new)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->next = NULL;
	}
}

t_spr_list		*sort_spr(t_all *all, t_spr_list **ph)
{
	all->out = NULL;
	while (*ph)
	{
		all->q = *ph;
		*ph = (*ph)->next;
		all->p = all->out;
		all->pr = NULL;
		while (all->p && all->q->len_from_plr < all->p->len_from_plr)
		{
			all->pr = all->p;
			all->p = all->p->next;
		}
		if (all->pr == NULL)
		{
			all->q->next = all->out;
			all->out = all->q;
		}
		else
		{
			all->q->next = all->p;
			all->pr->next = all->q;
		}
	}
	*ph = all->out;
	return (*ph);
}

void			get_spr_list(t_all *all, int i, int j)
{
	int		x;
	int		y;

	x = SCALE * j + (SCALE / 2);
	y = SCALE * i + (SCALE / 2);
	ft_spr_lstadd_back(&all->spr_list, ft_spr_lstnew(x, y, 0));
}
