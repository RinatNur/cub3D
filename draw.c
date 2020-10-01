#include "cub3D.h"

void 	init_ray_begin(t_all *all)
{
	all->x = 0;
	all->ray.start = all->plr.dir - FOV/2;
	all->ray.end = all->plr.dir + FOV/2;
	all->ray.len = 0;
	all->ray.x = all->plr.x;
	all->ray.y = all->plr.y;
	all->ray.dir = all->ray.start;
	all->all_rays[WIN_W] = '\0';
}

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
		if (all->map[((int)all->ray.y) / (int)SCALE][((int) all->ray.x) / (int)SCALE] == '1')
		{
			break ;
		}
		all->ray.len += 0.25;
		all->ray.x = all->plr.x + all->ray.len * cos(all->ray.dir);
		all->ray.y = all->plr.y + all->ray.len * sin(all->ray.dir);
		my_mlx_pixel_put(&all->win.img, (int)all->ray.x/6, (int)all->ray.y/6, get_trgb(0, 255, 255, 255));
	}
}

void 	print_texture(t_all *all, double coordinate, t_texture *texture_type)
{
	all->coef = (double)texture_type->height / (double)all->wall.height;
	all->y_wall = (int)((all->wall.start - all->y_tmp) * all->coef);
	all->x_wall = (int)coordinate % all->texture_NO.width;
	my_mlx_pixel_put(&all->win.img, (int)all->x, all->wall.start, get_color(texture_type, (int)all->x_wall, (int)all->y_wall));
}

void 	check_and_print_texture(t_all *all)
{
	if (all->wall.start >= 0 && all->map[(int)all->ray.y / (int)SCALE][(int)(all->ray.x - 0.25 * cos(all->ray.dir)) / (int)SCALE] == '1')
		if(all->map[(int)(all->ray.y + 32) / (int)SCALE][(int)all->ray.x / (int)(SCALE)] == '1')
			print_texture(all, all->ray.x, &all->texture_NO);
		else
			print_texture(all, all->ray.x, &all->texture_SO);
	else if (all->wall.start >= 0)
	{
		if(all->map[(int)all->ray.y / (int)SCALE][(int)(all->ray.x + 32) / (int)(SCALE)] == '1')
			print_texture(all, all->ray.y, &all->texture_EA);
		else
			print_texture(all, all->ray.y, &all->texture_WE);
	}
}

void 	draw_walls(t_all *all)
{
	all->ray.len *= cos(-all->ray.dir + all->plr.dir);
	all->wall.start = WIN_H / 2 - (WIN_H  / all->ray.len * SCALE) /2;
	all->wall.end = WIN_H / 2 + (WIN_H  / all->ray.len * SCALE) /2;
	if (all->wall.end > WIN_H)
		all->wall.end = WIN_H - 1;
	if (all->wall.start < 0)
		all->wall.start = 0;
	all->wall.height = all->wall.end - all->wall.start;
	all->y_tmp = all->wall.start;
	while (all->wall.start < all->wall.end && all->wall.end < WIN_W)
	{
		check_and_print_texture(all);
		all->wall.start++;
	}
}

void 	ray_casting(t_all *all)
{
	init_ray_begin(all);
	while (all->ray.dir < all->ray.end)
	{
		one_ray_casting(all);
		draw_walls(all);
		all->x++;
		init_ray_cicle(all);
	}
}

void 	draw_img(t_all *all)
{
	mlx_destroy_image(all->win.mlx, all->win.img.img);
	all->win.img.img = mlx_new_image(all->win.mlx, WIN_W, WIN_H);
	all->win.img.addr = mlx_get_data_addr(all->win.img.img, &all->win.img.bits_per_pixel, &all->win.img.line_length,
										  &all->win.img.endian);
	ray_casting(all);
	draw_map(all);
	mlx_put_image_to_window(all->win.mlx, all->win.mlx_win, all->win.img.img, 0, 0);
}