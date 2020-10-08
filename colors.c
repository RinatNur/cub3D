#include "cub3D.h"

int 		get_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	if (y < WIN_H && x < WIN_W)
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
