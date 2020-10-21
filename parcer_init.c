/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:45:55 by jheat             #+#    #+#             */
/*   Updated: 2020/10/21 17:49:41 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		init_parcer(t_all *all)
{
	all->head = NULL;
	all->no_t = NULL;
	all->so_t = NULL;
	all->we_t = NULL;
	all->ea_t = NULL;
	all->s_t = NULL;
	all->win_w = -1;
	all->win_h = -1;
	all->floor_col = -1;
	all->ceiling_col = -1;
	all->plr.x = -1;
	all->plr.y = -1;
	all->plr.flag = 0;
}

void		init_lines_len(t_all *all, char **map, int i)
{
	all->len.last_in = 0;
	while (map[all->len.last_in])
		all->len.last_in++;
	all->len.last_in -= 1;
	all->len.this = (int)ft_strlen(map[i]) - 1;
	all->len.first = (int)ft_strlen(map[0]) - 1;
	all->len.up = (i > 0) ? (int)(ft_strlen(map[i - 1]) - 1) : 0;
	all->len.down = (i < all->len.last_in)
			? (int)(ft_strlen(map[i + 1]) - 1) : 0;
	all->len.last = (int)ft_strlen(map[all->len.last_in]) - 1;
}

void		init_plr(t_all *all, int i, int j)
{
	all->plr.flag == 1 ? exit_err("More than one player", 55) : 0;
	all->plr.flag = 1;
	all->plr.x = SCALE * j + (SCALE / 2);
	all->plr.y = SCALE * i + (SCALE / 2);
	all->plr.dir = ft_plr_vision(all->map[i][j]);
}
