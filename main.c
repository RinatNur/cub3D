/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:00:46 by jheat             #+#    #+#             */
/*   Updated: 2020/10/18 17:00:46 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		init_textures(t_all *all)
{
	all->texture_NO.img = mlx_xpm_file_to_image(all->win.mlx, all->no_text, &all->texture_NO.width, &all->texture_NO.height);

	all->texture_SO.img = mlx_xpm_file_to_image(all->win.mlx, all->so_text, &all->texture_SO.width, &all->texture_SO.height);

	all->texture_WE.img = mlx_xpm_file_to_image(all->win.mlx, all->we_text, &all->texture_WE.width, &all->texture_WE.height);

	all->texture_EA.img = mlx_xpm_file_to_image(all->win.mlx, all->ea_text, &all->texture_EA.width, &all->texture_EA.height);

	all->texture_S.img = mlx_xpm_file_to_image(all->win.mlx, all->s_text, &all->texture_S.width, &all->texture_S.height);
	if (all->texture_NO.img && all->texture_SO.img && all->texture_WE.img && all->texture_EA.img && all->texture_S.img)
	{
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
	} else
		exit_err("Not valid textures", 12);
}

static int		close_with_red_x(int code)
{
	if (!code)
		exit(0);
	return (1);
}

void			exit_err(char *str, int code)
{
	write(2, "Error\n", 6);
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
	exit (code);
}

static void 	check_argc(t_all *all, int argc, char **argv)
{
	int len;

	len = ft_strlen(argv[1]);
	if (argc == 3)
		if (ft_strlen(argv[2]) != 6 || ft_strncmp(argv[2], "--save", 6))
			exit_err("Not valid input data", 2);
	if (argc == 2)
		if (len < 5 || ft_strncmp(&argv[1][len - 4], ".cub", 4))
			exit_err("Not valid name of map file", 2);
}

int				main(int argc, char **argv)
{
	t_all		all;
	int			fd;

	(argc < 2 || argc > 3) ? exit_err("Not valid input data", 2)
	: check_argc(&all, argc, argv);
	all.count = 0;
	(fd = open (argv[1], O_RDONLY)) == -1 ? exit_err("The file can't be opened", 2) : 0;
	ft_parcer(&all, fd);
	all.win.mlx = mlx_init();
	all.win.mlx_win = mlx_new_window(all.win.mlx, all.win_w, all.win_h, "cub 3D!");
	!(all.win.img.img = mlx_new_image(all.win.mlx, all.win_w, all.win_h)) ? exit_err("No image", 2) : 0;
	all.win.img.addr = mlx_get_data_addr(all.win.img.img, &all.win.img.bits_per_pixel, &all.win.img.line_length,
										  &all.win.img.endian);
	init_textures(&all);
	draw_img(&all);
	mlx_put_image_to_window(all.win.mlx, all.win.mlx_win, all.win.img.img, 0, 0);
	mlx_hook(all.win.mlx_win, 2, 1L, ft_move, &all);
	mlx_hook(all.win.mlx_win, 17, 1L, close_with_red_x, 0);
	if (argc == 3)
		make_screenshot(&all);
	mlx_loop(all.win.mlx);
}