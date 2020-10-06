#include "cub3D.h"

static void 	move_left_or_right(int keycode, t_all *all)
{
	if (LEFT)
	{
		if ((all->map)[(int)((all->plr.y - cos(all->plr.dir) * 21) / SCALE)]
			[(int)((all->plr.x + sin(all->plr.dir) * 21) / SCALE)] != '1')
		{
			all->plr.x += sin(all->plr.dir) * 21;
			all->plr.y -= cos(all->plr.dir) * 21;
			draw_img(all);
		}
	}
	if (RIGHT)
	{
		if ((all->map)[(int)((all->plr.y + cos(all->plr.dir) * 21) / SCALE)]
			[(int)((all->plr.x - sin(all->plr.dir) * 21) / SCALE)] != '1')
		{
			all->plr.x -= sin(all->plr.dir) * 21;
			all->plr.y += cos(all->plr.dir) * 21;
			draw_img(all);
		}
	}
}

static void 	move_up_or_down(int keycode, t_all *all)
{	int 	i, j;
	double  k, n;

	if (UP)
	{
		i = (int)((all->plr.y + sin(all->plr.dir) * 21) / SCALE);
		j = (int)((all->plr.x + cos(all->plr.dir) * 21) / SCALE);
		if (all->map[i][j] != '1')
		{
			all->plr.x += cos(all->plr.dir) * 21;
			all->plr.y += sin(all->plr.dir) * 21;
			draw_img(all);
		}
	}
	if (DOWN)
	{
		if ((all->map)[(int)((all->plr.y - sin(all->plr.dir) * 21) / SCALE)]
			[(int)((all->plr.x - cos(all->plr.dir) * 21) / SCALE)] != '1')
		{
			all->plr.x -= cos(all->plr.dir) * 21;
			all->plr.y -= sin(all->plr.dir) * 21;
			draw_img(all);
		}
	}
}

int 		ft_move(int keycode, t_all *all)
{

	if (LEFT || RIGHT)
		move_left_or_right(keycode, all);
	if (UP || DOWN)
		move_up_or_down(keycode, all);
	if (LOOK_L)
	{
		all->plr.dir = all->plr.dir - 0.1;
		draw_img(all);
	}
	if (LOOK_R)
	{
		all->plr.dir = all->plr.dir + 0.1;
		draw_img(all);
	}
	if (ESC)
		exit(0);
	return(0);
}

