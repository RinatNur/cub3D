/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:00:46 by jheat             #+#    #+#             */
/*   Updated: 2020/10/20 18:55:27 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		init_textures(t_all *all)
{
	all->T_NO.img = mlx_xpm_file_to_image(all->win.mlx, all->no_t,
			&all->T_NO.width, &all->T_NO.height);
	all->T_SO.img = mlx_xpm_file_to_image(all->win.mlx, all->so_t,
			&all->T_SO.width, &all->T_SO.height);
	all->T_WE.img = mlx_xpm_file_to_image(all->win.mlx, all->we_t,
			&all->T_WE.width, &all->T_WE.height);
	all->T_EA.img = mlx_xpm_file_to_image(all->win.mlx, all->ea_t,
			&all->T_EA.width, &all->T_EA.height);
	all->T_S.img = mlx_xpm_file_to_image(all->win.mlx, all->s_t,
			&all->T_S.width, &all->T_S.height);
	if (all->T_NO.I && all->T_SO.I && all->T_WE.I && all->T_EA.I && all->T_S.I)
	{
		all->T_S.addr = mlx_get_data_addr(all->T_S.img, &all->T_S.BPP,
				&all->T_S.line_length, &all->T_S.endian);
		all->T_NO.addr = mlx_get_data_addr(all->T_NO.img, &all->T_NO.BPP,
				&all->T_NO.line_length, &all->T_NO.endian);
		all->T_SO.addr = mlx_get_data_addr(all->T_SO.img, &all->T_SO.BPP,
				&all->T_SO.line_length, &all->T_SO.endian);
		all->T_WE.addr = mlx_get_data_addr(all->T_WE.img, &all->T_WE.BPP,
				&all->T_WE.line_length, &all->T_WE.endian);
		all->T_EA.addr = mlx_get_data_addr(all->T_EA.img, &all->T_EA.BPP,
				&all->T_EA.line_length, &all->T_EA.endian);
	}
	else
		exit_err("Not valid textures", 44);
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
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(code);
}

static void		check_argc(int argc, char **argv)
{
	int len;

	len = ft_strlen(argv[1]);
	if (argc == 3)
		if (ft_strlen(argv[2]) != 6 || ft_strncmp(argv[2], "--save", 6))
			exit_err("Not valid input data", 88);
	if (len < 5 || ft_strncmp(&argv[1][len - 4], ".cub", 4))
		exit_err("Not valid name of map file", 88);
}

int				main(int argc, char **argv)
{
	t_all		all;
	int			fd;

	(argc < 2 || argc > 3) ? exit_err("Not valid input data", 88)
	: check_argc(argc, argv);
	(fd = open(argv[1], O_RDONLY)) == -1
	? exit_err("The file can't be opened", 77) : 0;
	ft_parcer(&all, fd);
	all.win.mlx = mlx_init();
	all.win.mlx_win = mlx_new_window(all.win.mlx, all.win_w,
			all.win_h, "cub3D");
	!(all.win.img.img = mlx_new_image(all.win.mlx, all.win_w, all.win_h))
			? exit_err("No image", 66) : 0;
	all.win.img.addr = mlx_get_data_addr(all.win.img.img, &all.win.img.BPP,
			&all.win.img.line_length, &all.win.img.endian);
	init_textures(&all);
	draw_img(&all);
	if (argc == 3)
		make_screenshot(&all);
	mlx_put_image_to_window(all.win.mlx, all.win.mlx_win,
			all.win.img.img, 0, 0);
	mlx_hook(all.win.mlx_win, 2, 1L, ft_move, &all);
	mlx_hook(all.win.mlx_win, 17, 1L, close_with_red_x, 0);
	mlx_loop(all.win.mlx);
}
