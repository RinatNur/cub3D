/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:01:36 by jheat             #+#    #+#             */
/*   Updated: 2020/10/19 16:35:45 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		create_bmp_header(t_all *all, int size, int fd)
{
	unsigned char		bmp_header[54];

	ft_bzero(bmp_header, 54);
	bmp_header[0] = (unsigned char)'B';
	bmp_header[1] = (unsigned char)'M';
	bmp_header[2] = (unsigned char)size;
	bmp_header[3] = (unsigned char)(size >> 8);
	bmp_header[4] = (unsigned char)(size >> 16);
	bmp_header[5] = (unsigned char)(size >> 24);
	bmp_header[10] = (unsigned char)54;
	bmp_header[14] = (unsigned char)40;
	bmp_header[18] = (unsigned char)all->win_w;
	bmp_header[19] = (unsigned char)(all->win_w >> 8);
	bmp_header[20] = (unsigned char)(all->win_w >> 16);
	bmp_header[21] = (unsigned char)(all->win_w >> 24);
	bmp_header[22] = (unsigned char)all->win_h;
	bmp_header[23] = (unsigned char)(all->win_h >> 8);
	bmp_header[24] = (unsigned char)(all->win_h >> 16);
	bmp_header[25] = (unsigned char)(all->win_h >> 24);
	bmp_header[26] = (unsigned char)1;
	bmp_header[28] = (unsigned char)24;
	write(fd, bmp_header, 54);
}

static void		print_pixels(t_all *all, int fd)
{
	unsigned int		color;
	int					y;
	int					x;

	y = all->win_h - 1;
	while (y >= 0)
	{
		x = -1;
		while (++x < all->win_w)
		{
			color = *(unsigned int *)(all->win.img.addr
					+ (y * all->win.img.line_length
					+ x * (all->win.img.bits_per_pixel / 8)));
			write(fd, &color, 3);
		}
		y--;
	}
}

void			make_screenshot(t_all *all)
{
	int		fd;
	int		size;

	if (all->win_w % 4)
		all->win_w = all->win_w - (all->win_w % 4);
	size = all->win_h * all->win_w + 54;
	if (!(fd = open("../screenshot.bmp", O_RDWR | O_CREAT, 0666)))
		exit_err("Screenshot failed", 2);
	create_bmp_header(all, size, fd);
	print_pixels(all, fd);
	close(fd);
	exit(0);
}
