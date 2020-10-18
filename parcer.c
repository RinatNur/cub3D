#include "cub3D.h"

static void 	init_parcer(t_all *all)
{
	all->head = NULL;
	all->r_text = NULL;
	all->no_text = NULL;
	all->so_text = NULL;
	all->we_text = NULL;
	all->ea_text = NULL;
	all->s_text = NULL;
	all->win_w = -1;
	all->win_h = -1;
	all->floor_col = -1;
	all->ceiling_col = -1;
	all->plr.x = -1;
	all->plr.y = -1;
	all->plr.flag = 0;

}

static void 	is_space_around_0_or_2_or_plr(char **map, int i, int j)
{
	int 	len_up;
	int 	len_down;
	int 	len;
	int 	len_end;
	int 	end;

	end = 0;
	while (map[end++]);
	end -= 2;
	len = (int)ft_strlen(map[i]) - 1;
	len_up = (i > 0) ? (int)(ft_strlen(map[i - 1]) - 1) : 0;
	len_down = (i < end) ? (int)(ft_strlen(map[i + 1]) - 1) : 0;
	len_end = (int)ft_strlen(map[end]) - 1;
	if (ft_strchr("02NSEW", map[0][j])
		|| (len_end >= j && (ft_strchr("02NSEW", map[end][j])))
		|| ft_strchr("02NSEW", map[i][0])
		|| ft_strchr("02NSEW", map[i][len])
		|| (i > 0 && i < end && j > 0 && j < len
		&& ((ft_strchr("02NSEW", map[i][j])
		&& (map[i][j - 1] == ' ' || map[i][j+1] == ' ' || map[i - 1][j] == ' '
		|| len_up < j || map[i + 1][j] == ' ' || len_down < j)))))
	{
		exit_err("Not valid map", 2);
	}
}

static char 	**make_map(t_all *all)
{
	char **map;
	int 	i;
	int 	size;
	t_list *tmp;

	size = ft_lstsize(all->head);
	map = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	tmp = all->head;

	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	map[++i] = NULL;
	return(map);
}

static void 	check_map_data(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (all->map[i] != NULL)
	{
		j = 0;
		while (all->map[i][j])
		{
			if (ft_strchr(" 012NSEW\n", (int)all->map[i][j]))
			{
				if (ft_strchr("02NSEW", all->map[i][j]))
					is_space_around_0_or_2_or_plr(all->map, i, j);
				if (ft_strchr("NSEW", all->map[i][j]))
				{
					all->plr.flag == 1 ? exit_err("More than one player", 2) : 0;
					all->plr.flag = 1;
					all->plr.x = SCALE * j + (SCALE / 2);
					all->plr.y = SCALE * i + (SCALE / 2);
					all->plr.dir = ft_plr_vision(all->map[i][j]);
				}
				else if (all->map[i][j] == '2')
				{
					get_spr_list(all, i, j);
				}
			} else
				exit_err("Map is not valid", 2);

			all->sprite_list_head = all->spr_list;
			j++;
		}
		i++;
	}
}

void 	ft_parcer(t_all *all, int fd)
{
	init_parcer(all);

	while ((get_next_line(fd, &all->line)) > 0)
	{
		if (*all->line != '\0')
		{
			check_line(all, all->line);
		}
		if (*all->line == '\0')
			free(all->line);
	}
	if (*all->line != '\0')
		check_line(all, all->line);
	if (*all->line == '\0')
		free(all->line);
	all->map = make_map(all);
	check_map_data(all);
	if (all->plr.x < 0 || all->plr.y < 0)
		exit_err("No player in map", 4);
	if(!(all->mas_rays = (double *)malloc(sizeof(double) * all->win_w + 1)))
		exit_err("Malloc error", 2);
}

