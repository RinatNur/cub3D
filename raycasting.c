/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:01:24 by jheat             #+#    #+#             */
/*   Updated: 2020/10/19 16:32:12 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		init_ray_begin(t_all *all)
{
	all->x = 0;
	all->ray.start = all->plr.dir - FOV / 2;
	all->ray.end = all->plr.dir + FOV / 2;
	all->ray.len = 0;
	all->ray.x = all->plr.x;
	all->ray.y = all->plr.y;
	all->ray.dir = all->ray.start;
}

static void		init_ray_cicle(t_all *all)
{
	all->ray.len = 0;
	all->ray.x = all->plr.x;
	all->ray.y = all->plr.y;
	all->ray.dir += FOV / all->win_w;
}

static void		one_ray_casting(t_all *all)
{
	while (1)
	{
		if (all->map[(int)(all->ray.y / SCALE)][(int)(all->ray.x / SCALE)]
				== '1'
		|| (all->map[((int)all->ray.y + 1) / (int)SCALE][((int)all->ray.x + 1)
			/ (int)SCALE] == '1'
		&& all->map[((int)all->ray.y - 1) / (int)SCALE][((int)all->ray.x - 1)
			/ (int)SCALE] == '1')
		|| (all->map[((int)all->ray.y - 1) / (int)SCALE][((int)all->ray.x + 1)
			/ (int)SCALE] == '1'
		&& all->map[((int)all->ray.y + 1) / (int)SCALE][((int)all->ray.x - 1)
			/ (int)SCALE] == '1'))
			break ;
		all->ray.len += STEP;
		all->ray.x = all->plr.x + all->ray.len * cos(all->ray.dir);
		all->ray.y = all->plr.y + all->ray.len * sin(all->ray.dir);
	}
}

void			ray_casting(t_all *all)
{
	init_ray_begin(all);
	while (all->ray.dir < all->ray.end)
	{
		one_ray_casting(all);
		all->mas_rays[(int)all->x] = all->ray.len;
		all->x++;
		draw_walls(all);
		init_ray_cicle(all);
	}
}
