/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:01:12 by jheat             #+#    #+#             */
/*   Updated: 2020/10/21 17:53:20 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		is_space_around_0_2_plr(t_all *all, char **map, int i, int j)
{
	init_lines_len(all, map, i);
	if (
		(all->len.first >= j && ft_strchr("02NSEW", map[0][j]))
		|| (all->len.last >= j && (ft_strchr("02NSEW",
				map[all->len.last_in][j])))
		|| ft_strchr("02NSEW", map[i][0])
		|| ft_strchr("02NSEW", map[i][0])
		|| ft_strchr("02NSEW", map[i][all->len.this])
		|| (0 < j && j < all->len.this
		&& ((ft_strchr("02NSEW", map[i][j])
		&& (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || map[i - 1][j] == ' '
		|| all->len.up < j || map[i + 1][j] == ' ' || all->len.down < j)))))
	{
		exit_err("Not valid map", 55);
	}
}

static void		check_map_data(t_all *all)
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
					is_space_around_0_2_plr(all, all->map, i, j);
				if (ft_strchr("NSEW", all->map[i][j]))
					init_plr(all, i, j);
				else if (all->map[i][j] == '2')
					get_spr_list(all, i, j);
			}
			else
				exit_err("Map is not valid", 55);
			all->sprite_list_head = all->spr_list;
			j++;
		}
		i++;
	}
}

static char		**make_map(t_all *all)
{
	char		**map;
	int			i;
	int			size;
	t_list		*tmp;

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
	return (map);
}

void			ft_parcer(t_all *all, int fd)
{
	init_parcer(all);
	while ((get_next_line(fd, &all->line)) > 0)
	{
		if ((ft_lstsize(all->head) > 0) && *all->line == '\0')
			exit_err("Map is not valid", 55);
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
		exit_err("No player in map", 55);
	if (!(all->mas_rays = (double *)malloc(sizeof(double) * all->win_w + 1)))
		exit_err("Malloc: memory is not allocated", 33);
}
