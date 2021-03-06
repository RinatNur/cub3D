/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:59:41 by jheat             #+#    #+#             */
/*   Updated: 2020/10/19 19:25:57 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char		*dst;

	if (0 <= y && y < all->win_h && 0 <= x && x < all->win_w)
	{
		dst = all->win.img.addr + (y * all->win.img.line_length
				+ x * (all->win.img.bits_per_pixel) / 8);
		*(unsigned int *)dst = color;
	}
}

int			get_color(t_texture *texture, int x, int y)
{
	char		*dst;

	dst = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	return (*(int*)dst);
}
