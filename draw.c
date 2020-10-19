/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:00:21 by jheat             #+#    #+#             */
/*   Updated: 2020/10/18 19:56:43 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		print_texture(t_all *all, double coordinate, t_texture *tex)
{
	all->y_wall = (int)((all->wall.start - all->y_tmp) * tex->height
					/ (all->wall.end - all->y_tmp));
	all->x_wall = (int)(coordinate * (tex->width / SCALE)) % tex->width;
	my_mlx_pixel_put(all, (int)all->x, all->wall.start,
				get_color(tex, (int)all->x_wall, (int)all->y_wall));
}

void		check_and_print_texture(t_all *all)
{
	if (all->wall.start >= 0 && all->map[(int)all->ray.y
		/ (int)SCALE][(int)(all->ray.x - STEP * cos(all->ray.dir))
		/ (int)SCALE] == '1')
		if (all->map[(int)(all->ray.y + 32) / (int)SCALE][(int)all->ray.x
			/ (int)(SCALE)] == '1')
			print_texture(all, all->ray.x, &all->texture_no);
		else
			print_texture(all, all->ray.x, &all->texture_so);
	else if (all->wall.start >= 0)
	{
		if (all->map[(int)all->ray.y / (int)SCALE][(int)(all->ray.x + 32)
			/ (int)(SCALE)] == '1')
			print_texture(all, all->ray.y, &all->texture_ea);
		else
			print_texture(all, all->ray.y, &all->texture_we);
	}
}

void		draw_walls(t_all *all)
{
	int		i;

	i = -1;
	all->ray.len *= cos(all->plr.dir - all->ray.dir);
	all->wall.start = all->win_h / 2 - (int)(all->win_h
			/ all->ray.len * SCALE) / 2;
	all->wall.end = all->win_h / 2 + (int)(all->win_h
			/ all->ray.len * SCALE) / 2;
	all->y_tmp = all->wall.start;
	while (i++ < all->wall.start + 5)
		my_mlx_pixel_put(all, (int)all->x, i, all->ceiling_col);
	i = all->wall.end - 5;
	while (i++ < all->win_h)
		my_mlx_pixel_put(all, (int)all->x, i, all->floor_col);
	while (all->wall.start < all->wall.end && all->wall.start < all->win_h)
	{
		check_and_print_texture(all);
		all->wall.start++;
	}
}

void		draw_img(t_all *all)
{
	mlx_destroy_image(all->win.mlx, all->win.img.img);
	all->win.img.img = mlx_new_image(all->win.mlx, all->win_w, all->win_h);
	all->win.img.addr = mlx_get_data_addr(all->win.img.img,
			&all->win.img.bits_per_pixel,
			&all->win.img.line_length, &all->win.img.endian);
	all->spr_list = all->sprite_list_head;
	while (all->spr_list)
	{
		all->spr_list->len_from_plr = (int)sqrt((pow(all->plr.x
				- all->spr_list->spr_x, 2)
				+ (pow(all->plr.y - all->spr_list->spr_y, 2))));
		all->spr_list = all->spr_list->next;
	}
	sort_spr(all, &all->sprite_list_head);
	all->spr_list = all->sprite_list_head;
	ray_casting(all);
	while (all->spr_list)
	{
		draw_spr(all, all->spr_list);
		all->spr_list = all->spr_list->next;
	}
	mlx_put_image_to_window(all->win.mlx, all->win.mlx_win,
			all->win.img.img, 0, 0);
}
