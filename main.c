#include "cub3D.h"

void 	init_textures(t_all *all)
{
	all->texture_NO.img = mlx_xpm_file_to_image(all->win.mlx, all->no_text, &all->texture_NO.width, &all->texture_NO.height);

	all->texture_SO.img = mlx_xpm_file_to_image(all->win.mlx, all->so_text, &all->texture_SO.width, &all->texture_SO.height);

	all->texture_WE.img = mlx_xpm_file_to_image(all->win.mlx, all->we_text, &all->texture_WE.width, &all->texture_WE.height);

	all->texture_EA.img = mlx_xpm_file_to_image(all->win.mlx, all->ea_text, &all->texture_EA.width, &all->texture_EA.height);

	all->texture_S.img = mlx_xpm_file_to_image(all->win.mlx, all->s_text, &all->texture_S.width, &all->texture_S.height);
//	if (all->texture_NO.img && all->texture_SO.img && all->texture_WE.img && all->texture_EA.img && all->texture_S.img)
//	{
	all->texture_S.addr = mlx_get_data_addr(all->texture_S.img, &all->texture_S.bits_per_pixel, &all->texture_S.line_length,
											 &all->texture_S.endian);
	all->texture_NO.addr = mlx_get_data_addr(all->texture_NO.img, &all->texture_NO.bits_per_pixel, &all->texture_NO.line_length,
											 &all->texture_NO.endian);
	all->texture_SO.addr = mlx_get_data_addr(all->texture_SO.img, &all->texture_SO.bits_per_pixel, &all->texture_SO.line_length,
											 &all->texture_SO.endian);
	all->texture_WE.addr = mlx_get_data_addr(all->texture_WE.img, &all->texture_WE.bits_per_pixel, &all->texture_WE.line_length,
											 &all->texture_WE.endian);
	all->texture_EA.addr = mlx_get_data_addr(all->texture_EA.img, &all->texture_EA.bits_per_pixel, &all->texture_EA.line_length,
											 &all->texture_EA.endian);
//	} else
//		exit_err("Not valid textures", 12);
}

static int		close_with_red_x(int code)
{
	if (!code)
		exit(0);
	return (1);
}

void 	list_print (t_spr_list *list)
{
	t_spr_list		*temp;

	temp = list;
	while (list != NULL)
	{
		printf("x.spr = %i, y.spr = %i len = %i \n", list->spr_x, list->spr_y, list->len_from_plr);
		list = list->next;
	}
}

int		main(int argc, char **argv)
{
	t_all		all;

	all.count = 0;
//	all.map = make_map(&all);
	ft_parcer(&all);
	find_plr(&all);
	all.win.mlx = mlx_init();
	all.win.mlx_win = mlx_new_window(all.win.mlx, WIN_W, WIN_H, "cub 3D!");
	all.win.img.img = mlx_new_image(all.win.mlx, WIN_W, WIN_H);
	all.win.img.addr = mlx_get_data_addr(all.win.img.img, &all.win.img.bits_per_pixel, &all.win.img.line_length,
										  &all.win.img.endian);
	init_textures(&all);
	draw_img(&all);
	mlx_put_image_to_window(all.win.mlx, all.win.mlx_win, all.win.img.img, 0, 0);
	mlx_hook(all.win.mlx_win, 2, 1L, ft_move, &all);
	mlx_hook(all.win.mlx_win, 17, 1L, close_with_red_x, 0);
	mlx_loop(all.win.mlx);
}