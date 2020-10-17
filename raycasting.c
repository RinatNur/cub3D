#include "cub3D.h"

static void 	init_ray_begin(t_all *all)
{
	all->x = 0;
	all->ray.start = all->plr.dir - FOV/2;
	all->ray.end = all->plr.dir + FOV/2;
	all->ray.len = 0;
	all->ray.x = all->plr.x;
	all->ray.y = all->plr.y;
	all->ray.dir = all->ray.start;

}

static void 	init_ray_cicle(t_all *all)
{
	all->ray.len = 0;
	all->ray.x = all->plr.x;
	all->ray.y = all->plr.y;
	all->ray.dir += FOV / all->win_w;
}

static void 	one_ray_casting(t_all *all)
{

	while (1)
	{
//		printf("len = %2.f\n", all->ray.len);
		if (all->map[((int)all->ray.y) / (int)SCALE][((int) all->ray.x) / (int)SCALE] == '1' // || all->ray.len > 900)
			|| (all->map[((int)all->ray.y + 1) / (int)SCALE][((int) all->ray.x + 1) / (int)SCALE] == '1'
			   && all->map[((int)all->ray.y - 1) / (int)SCALE][((int) all->ray.x - 1) / (int)SCALE] == '1')
			|| (all->map[((int)all->ray.y - 1) / (int)SCALE][((int) all->ray.x + 1) / (int)SCALE] == '1'
			   && all->map[((int)all->ray.y + 1) / (int)SCALE][((int) all->ray.x - 1) / (int)SCALE] == '1'))
			break ;
		all->ray.len += 0.25;
		all->ray.x = all->plr.x + all->ray.len * cos(all->ray.dir);
		all->ray.y = all->plr.y + all->ray.len * sin(all->ray.dir);
		my_mlx_pixel_put(all, &all->win.img, (int)all->ray.x/6, (int)all->ray.y/6, get_trgb(0, 85, 21, 78));
	}
}

void 			ray_casting(t_all *all)
{
	int			i = 0;
	double		j =0;
//	if(!(all->mas_rays = (double *)malloc(sizeof(double) * all->win_w + 1)))
//	{
//		free(all->mas_rays);
//		exit_err("Malloc error", 2);
//	}
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
//	while (all->ray.dir < all->ray.end)
//	{
//		while (all->ray.len < all->mas_rays[i])
//		{
//			all->ray.len += 0.25;
//			all->ray.x = all->plr.x + all->ray.len * cos(all->ray.dir);
//			all->ray.y = all->plr.y + all->ray.len * sin(all->ray.dir);
//			if (abs((int)(all->mas_rays[i - 3] - all->mas_rays[i + 3] )) < SCALE
//				&& abs((int)(all->mas_rays[i] - all->mas_rays[i - 3] )) > SCALE)
//			{
//				all->mas_rays[i] = all->mas_rays[i - 3];
//				all->ray.len = all->mas_rays[i - 3];
//			}
//
//			my_mlx_pixel_put(all, &all->win.img, (int)all->ray.x/6, (int)all->ray.y/6, get_trgb(0, 85, 21, 78));
//		}
//		init_ray_cicle(all);
//		i++;
//	}
}

