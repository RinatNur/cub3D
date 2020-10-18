/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:59:41 by jheat             #+#    #+#             */
/*   Updated: 2020/10/18 16:59:41 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int 		get_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void		my_mlx_pixel_put(t_all *all, t_data *data, int x, int y, int color)
{
	char		*dst;

	if (0 <= y && y < all->win_h && 0 <= x &&  x < all->win_w)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel) / 8);
		*(unsigned int *) dst = color;
	}
}

int            get_color(t_texture *texture, int x, int y)
{
	char    *dst;
	dst = texture->addr + (y * texture->line_length
						   + x * (texture->bits_per_pixel / 8));
	return (*(int*)dst);
}
