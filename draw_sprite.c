/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:00:35 by jheat             #+#    #+#             */
/*   Updated: 2020/10/18 20:00:01 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		spr_struct_init(t_all *all, t_spr_list *sprite)
{
	sprite->spr_dir = atan2((double)(sprite->spr_y - all->plr.y),
			(double)(sprite->spr_x - all->plr.x));
	while (sprite->spr_dir - all->plr.dir > M_PI)
		sprite->spr_dir -= 2 * M_PI;
	while (sprite->spr_dir - all->plr.dir < -M_PI)
		sprite->spr_dir += 2 * M_PI;
	sprite->spr_scr_size = (all->win_h) * SCALE / sprite->len_from_plr;
	sprite->h_offset = (sprite->spr_dir - all->plr.dir) * all->win_w
			/ (M_PI / 3) + all->win_w / 2 - sprite->spr_scr_size / 2;
	sprite->v_offset = all->win_h / 2 - sprite->spr_scr_size / 2;
	sprite->i = 0;
	sprite->j = 0;
	sprite->count = fabs(sprite->h_offset - all->mas_rays[0]);
	sprite->step = M_PI / (all->win_w * 3.0);
	sprite->color = 0;
}

static void		draw_spr_res(t_all *all, t_spr_list *sprite)
{
	while (sprite->j < sprite->spr_scr_size - 2)
	{
		if (sprite->v_offset + sprite->j < 0
			|| sprite->v_offset + sprite->j >= (int)all->win_h)
		{
			sprite->j++;
			continue;
		}
		sprite->color = get_color(&all->texture_s,
				(int)(sprite->i * (all->texture_s.width / SCALE) * SCALE
					/ sprite->spr_scr_size),
				(int)(sprite->j * (all->texture_s.height / SCALE) * SCALE
					/ sprite->spr_scr_size));
		if (sprite->color != 0x980088)
			my_mlx_pixel_put(all, sprite->h_offset + sprite->i,
					sprite->v_offset + sprite->j, sprite->color);
		sprite->j++;
	}
	sprite->step += M_PI / (all->win_w * 3.0);
	sprite->j = 0;
	sprite->i++;
	sprite->count++;
}

void			draw_spr(t_all *all, t_spr_list *sprite)
{
	spr_struct_init(all, sprite);
	if (sprite->spr_scr_size > 2000)
		sprite->spr_scr_size = 0;
	while (sprite->i < sprite->spr_scr_size)
	{
		if (sprite->h_offset + sprite->i < 0 ||
			sprite->h_offset + sprite->i >= all->win_w)
		{
			sprite->i++;
			continue;
		}
		if (all->mas_rays[(int)((int)sprite->h_offset + sprite->i)]
				< sprite->len_from_plr)
		{
			sprite->i++;
			continue;
		}
		draw_spr_res(all, sprite);
	}
}
