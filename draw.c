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
			my_mlx_pixel_put(all, &all->win.img, (int)x, (int)y, trgb);
			x++;
		}
		x = start_x;
		y++;
	}
}

void	draw_map(t_all *all)
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

void 	print_texture(t_all *all, double coordinate, t_texture *texture_type)
{
	all->y_wall = (int)((all->wall.start - all->y_tmp) * texture_type->height / (all->wall.end - all->y_tmp));
	all->x_wall = (int)coordinate % all->texture_NO.width;
	my_mlx_pixel_put(all, &all->win.img, (int)all->x, all->wall.start,
					 get_color(texture_type, (int)all->x_wall, (int)all->y_wall));
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
	int i = -1;
	all->ray.len *= cos(all->plr.dir - all->ray.dir);
	all->wall.start = all->win_h / 2 - (all->win_h  / all->ray.len * SCALE) /2;
	all->wall.end = all->win_h / 2 + (all->win_h  / all->ray.len * SCALE) /2;
	all->y_tmp = all->wall.start;
	all->wall.height = all->wall.end - all->wall.start;
	while (i++ < all->wall.start + 5)
		my_mlx_pixel_put(all, &all->win.img, (int)all->x, i, all->ceiling_col);
	i = all->wall.end - 5;
	while (i++ < all->win_h)
		my_mlx_pixel_put(all, &all->win.img, (int)all->x, i, all->floor_col);
	while (all->wall.start < all->wall.end && all->wall.start < all->win_h)
	{
		check_and_print_texture(all);
		all->wall.start++;
	}
}

void	draw_img(t_all *all)
{

	mlx_destroy_image(all->win.mlx, all->win.img.img);
	all->win.img.img = mlx_new_image(all->win.mlx, all->win_w, all->win_h);
	all->win.img.addr = mlx_get_data_addr(all->win.img.img, &all->win.img.bits_per_pixel, &all->win.img.line_length,
										  &all->win.img.endian);
	all->spr_list = all->sprite_list_head;
	while (all->spr_list)
	{
		all->spr_list->len_from_plr = (int)sqrt((pow(all->plr.x - all->spr_list->spr_x, 2) + (pow(all->plr.y - all->spr_list->spr_y, 2))));
		all->spr_list = all->spr_list->next;
	}
	sort_spr(&all->sprite_list_head);
	all->spr_list = all->sprite_list_head;
	ray_casting(all);
	while (all->spr_list)
	{
		draw_spr(all, all->spr_list);
		all->spr_list = all->spr_list->next;
	}
//	draw_map(all);
	mlx_put_image_to_window(all->win.mlx, all->win.mlx_win, all->win.img.img, 0, 0);
}
