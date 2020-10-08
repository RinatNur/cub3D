#include "cub3D.h"

void 	ft_draw_square(t_all *all, int i, int j, double rec_per, int trgb)
{
	double		start_x;
	double		start_y;
	double 		x;
	double 		y;

	start_x = j * rec_per;
	start_y = i * rec_per;
	y = start_y;
	x = start_x;
 	while (y < start_y + rec_per)
	{
		while (x < start_x + rec_per)
		{
			my_mlx_pixel_put(&all->win.img, (int)x, (int)y, trgb);
			x++;
		}
		x = start_x;
		y++;
	}
}

void		draw_map(t_all *all)
{
	int 	i;
	int 	j;

	i = 0;
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '1')
				ft_draw_square(all, i, j, SCALE/6, get_trgb(0, 197, 217, 0));
			j++;
		}
		i++;
	}
}

void 	init_ray_begin(t_all *all)
{
	all->x = 0;
	all->ray.start = all->plr.dir - FOV/2;
	all->ray.end = all->plr.dir + FOV/2;
	all->ray.len = 0;
	all->ray.x = all->plr.x;
	all->ray.y = all->plr.y;
	all->ray.dir = all->ray.start;

}

void 	init_ray_cicle(t_all *all)
{
	all->ray.len = 0;
	all->ray.x = all->plr.x;
	all->ray.y = all->plr.y;
	all->ray.dir += FOV / WIN_W;
}

void 	one_ray_casting(t_all *all)
{
	while (1)
	{
		if (all->map[((int)all->ray.y) / (int)SCALE][((int) all->ray.x) / (int)SCALE] == '1'
			|| all->map[((int)all->ray.y + 1) / (int)SCALE][((int) all->ray.x + 1) / (int)SCALE] == '1'
			&& all->map[((int)all->ray.y - 1) / (int)SCALE][((int) all->ray.x - 1) / (int)SCALE] == '1'
			|| all->map[((int)all->ray.y - 1) / (int)SCALE][((int) all->ray.x + 1) / (int)SCALE] == '1'
			&& all->map[((int)all->ray.y + 1) / (int)SCALE][((int) all->ray.x - 1) / (int)SCALE] == '1')
			break ;
		all->ray.len += 0.15;
		all->ray.x = all->plr.x + all->ray.len * cos(all->ray.dir);
		all->ray.y = all->plr.y + all->ray.len * sin(all->ray.dir);
//
//		my_mlx_pixel_put(&all->win.img, (int)all->ray.x/6, (int)all->ray.y/6, get_trgb(0, 85, 21, 78));
	}
}

void 	print_texture(t_all *all, double coordinate, t_texture *texture_type)
{
/*	all->coef = (double)texture_type->height / (all->wall.end - all->y_tmp);//(double)all->wall.height;
	all->y_wall = (int)((all->wall.start - all->y_tmp) * all->coef);
	all->x_wall = (int)coordinate % all->texture_NO.width;
	my_mlx_pixel_put(&all->win.img, (int)all->x, all->wall.start,
			get_color(texture_type, (int)all->x_wall, (int)all->y_wall));*/
//	all->coef = ;//(double)all->wall.height;
	all->y_wall = (int)((all->wall.start - all->y_tmp) * texture_type->height / (all->wall.end - all->y_tmp));
	all->x_wall = (int)coordinate % all->texture_NO.width;
	my_mlx_pixel_put(&all->win.img, (int)all->x, all->wall.start,
					 get_color(texture_type, (int)all->x_wall, (int)all->y_wall));
}

void 	check_and_print_texture(t_all *all)
{
	if (all->wall.start >= 0 && all->map[(int)all->ray.y / (int)SCALE][(int)(all->ray.x - 0.25 * cos(all->ray.dir)) / (int)SCALE] == '1')
		if(all->map[(int)(all->ray.y + 32) / (int)SCALE][(int)all->ray.x / (int)(SCALE)] == '1')
			print_texture(all, all->ray.x, &all->texture_EA);
		else
			print_texture(all, all->ray.x, &all->texture_WE);
	else if (all->wall.start >= 0)
	{
		if(all->map[(int)all->ray.y / (int)SCALE][(int)(all->ray.x + 32) / (int)(SCALE)] == '1')
			print_texture(all, all->ray.y, &all->texture_NO);
		else
			print_texture(all, all->ray.y, &all->texture_SO);
	}
//	else
//		print_texture(all, all->ray.y, &all->texture_EA);
}

void 	draw_walls(t_all *all)
{
	int i = -1;
	all->ray.len *= cos(all->plr.dir - all->ray.dir);
	all->wall.start = WIN_H / 2 - (WIN_H  / all->ray.len * SCALE) /2;
	all->wall.end = WIN_H / 2 + (WIN_H  / all->ray.len * SCALE) /2;
	all->y_tmp = all->wall.start;
	all->wall.height = all->wall.end - all->wall.start;
	while (i++ < all->wall.start + 5)
		my_mlx_pixel_put(&all->win.img, (int)all->x, i, get_trgb(0, 46, 71, 213));
	i = all->wall.end - 5;
	while (i++ < WIN_H)
		my_mlx_pixel_put(&all->win.img, (int)all->x, i, get_trgb(0, 45, 45, 45));
	while (all->wall.start < all->wall.end && all->wall.start < WIN_H)
	{
		check_and_print_texture(all);
		all->wall.start++;
	}
}

void 	ray_casting(t_all *all)
{
	int i = 0;
	double j =0;
	all->mas_rays = (double *)malloc(sizeof(double) * WIN_W);
	init_ray_begin(all);
	while (all->ray.dir < all->ray.end)
	{
		one_ray_casting(all);
		all->mas_rays[(int)all->x] = all->ray.len;
		all->x++;
		draw_walls(all);
		init_ray_cicle(all);
	}
	init_ray_begin(all);
	while (all->ray.dir < all->ray.end)
	{
		while (all->ray.len < all->mas_rays[i])
		{
			all->ray.len += 0.25;
			all->ray.x = all->plr.x + all->ray.len * cos(all->ray.dir);
			all->ray.y = all->plr.y + all->ray.len * sin(all->ray.dir);
			if (abs((int)(all->mas_rays[i - 3] - all->mas_rays[i + 3] )) < SCALE
				&& abs((int)(all->mas_rays[i] - all->mas_rays[i - 3] )) > SCALE)
			{
				all->mas_rays[i] = all->mas_rays[i - 3];
				all->ray.len = all->mas_rays[i - 3];
			}
			my_mlx_pixel_put(&all->win.img, (int)all->ray.x/6, (int)all->ray.y/6, get_trgb(0, 85, 21, 78));
		}
		init_ray_cicle(all);
		i++;
	}
}

void 	spr_struct_init(t_all *all, t_spr_list *sprite)
{
		sprite->spr_dir = atan2(sprite->spr_y - all->plr.y, sprite->spr_x - all->plr.x);
		while (sprite->spr_dir - all->plr.dir > M_PI)
			sprite->spr_dir -= 2 * M_PI;
		while (sprite->spr_dir - all->plr.dir < -M_PI)
			sprite->spr_dir += 2 * M_PI;
		sprite->spr_scr_size = WIN_H * 64 / sprite->len_from_plr;
		sprite->h_offset = (sprite->spr_dir - all->plr.dir) * WIN_W
						   / (M_PI / 3) + WIN_W / 2 - sprite->spr_scr_size / 2;
		sprite->v_offset = WIN_H / 2 - sprite->spr_scr_size / 2;
		sprite->i = 0;
		sprite->j = 0;
		sprite->count = fabs(sprite->h_offset - all->mas_rays[0]);
		sprite->step = M_PI / (WIN_W * 3.0);
		sprite->color = 0;

}

void 	draw_spr_res(t_all *all, t_spr_list *sprite)
{
	while (sprite->j < sprite->spr_scr_size - 2)
	{
		if (sprite->v_offset + sprite->j < 0
		|| sprite->v_offset + sprite->j >= (int)WIN_H)
		{
			sprite->j++;
			continue;
		}
		sprite->color = get_color(&all->texture_S, sprite->i * SCALE / sprite->spr_scr_size,
				sprite->j * SCALE / sprite->spr_scr_size);
		if (sprite->color != 0x980088)
			my_mlx_pixel_put(&all->win.img, sprite->h_offset + sprite->i, // changed all to &all->win.img
					sprite->v_offset + sprite->j, sprite->color);
		sprite->j++;
	}
	sprite->step += M_PI / (WIN_W * 3.0);
	sprite->j = 0;
	sprite->i++;
	sprite->count++;
}

void 	draw_spr(t_all *all, t_spr_list *sprite)
{
	int i =0;

	spr_struct_init(all, sprite);
	if (sprite->spr_scr_size > 2000)
		sprite->spr_scr_size = 0;
	while (sprite->i < sprite->spr_scr_size)
	{
   		if (sprite->h_offset + sprite->i < 0 ||
		sprite->h_offset + sprite->i >= WIN_W)
		{
			sprite->i++;
			continue;
		}
		if (all->mas_rays[(int)((int)sprite->h_offset + sprite->i)] < sprite->len_from_plr)
		{
				sprite->i++;
				continue;
		}
		draw_spr_res(all, sprite);
	}
}

void 	draw_img(t_all *all)
{
	mlx_destroy_image(all->win.mlx, all->win.img.img);
	all->win.img.img = mlx_new_image(all->win.mlx, WIN_W, WIN_H);
	all->win.img.addr = mlx_get_data_addr(all->win.img.img, &all->win.img.bits_per_pixel, &all->win.img.line_length,
										  &all->win.img.endian);
	find_spr(all);
	ray_casting(all);
	while (all->spr_list)
	{
		draw_spr(all, all->spr_list);
		all->spr_list = all->spr_list->next;
	}
	draw_map(all);
	mlx_put_image_to_window(all->win.mlx, all->win.mlx_win, all->win.img.img, 0, 0);
}