/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 13:37:05 by jheat             #+#    #+#             */
/*   Updated: 2020/10/19 17:28:20 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		is_ident_true(t_all *all)
{
	if (all->no_t && all->so_t && all->we_t && all->ea_t && all->s_t
		&& all->floor_col >= 0 && all->ceiling_col >= 0 && all->win_h >= 0
		&& all->win_w >= 0)
		return (1);
	return (0);
}

static void		is_r_f_c_valid(char *s, char c, int j, char *err)
{
	int		i;

	i = 0;
	while (j > 0)
	{
		if ('0' <= s[i] && s[i] <= '9')
			while (('0' <= s[i] && s[i] <= '9'))
				i++;
		else
			exit_err(err, 2);
		if (s[i] == c)
			i++;
		else if (j != 1)
			exit_err(err, 2);
		if (c == ' ')
			while (s[i] == ' ')
				i++;
		j--;
	}
	if (s[i] != '\0')
		exit_err(err, 2);
}

static void		get_scr_size(t_all *all, char *line)
{
	char		**size;
	int			i;
	int			j;

	j = 0;
	line = ft_strtrim(line, " ");
	is_r_f_c_valid(line, ' ', 2, "Not valid screen size");
	size = ft_split(line, ' ');
	free(line);
	if (!(i = 0) && NULL == size)
		exit_err("Malloc: memory is not allocated", 33);
	while (size[i])
	{
		while (size[i][j])
			j++;
		if (j > 11)
			exit_err("Not valid screen size", 2);
		i++;
	}
	mlx_get_screen_size(all->win.mlx_win, &all->scr_size_x, &all->scr_size_y);
	all->win_w = ft_atoi(size[0]);
	all->win_h = ft_atoi(size[1]);
	all->win_w = (all->win_w > all->scr_size_x) ? all->scr_size_x : all->win_w;
	all->win_h = (all->win_h > all->scr_size_y) ? all->scr_size_y : all->win_h;
	ft_free_mas(size);
}

static int		get_f_and_c_col(char *s)
{
	char		**rgb;
	char		*line;
	int			r;
	int			g;
	int			b;

	line = s;
	is_r_f_c_valid(line, ',', 3, "Not valid Floor Or Ceil color");
	rgb = ft_split(line, ',');
	if (NULL == rgb)
	{
		free(rgb);
		exit_err("Malloc: memory is not allocated", 33);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_mas(rgb);
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		exit_err("Not valid Floor Or Ceil color", 2);
	free(line);
	return (0 << 24 | r << 16 | g << 8 | b);
}

void			check_line(t_all *all, char *s)
{
	char		*li;

	li = skip_space(s);
	if (*li == 'R' && *(li + 1) == ' ' && all->win_h == -1 && all->win_w == -1)
		get_scr_size(all, li + 1);
	else if (*li == 'N' && *(li + 1) == 'O' && !all->no_t)
		all->no_t = ft_strtrim(li + 2, " ");
	else if (*li == 'S' && *(li + 1) == 'O' && !all->so_t)
		all->so_t = ft_strtrim(li + 2, " ");
	else if (*li == 'W' && *(li + 1) == 'E' && !all->we_t)
		all->we_t = ft_strtrim(li + 2, " ");
	else if (*li == 'E' && *(li + 1) == 'A' && !all->ea_t)
		all->ea_t = ft_strtrim(li + 2, " ");
	else if (*li == 'S' && *(li + 1) == ' ' && !all->s_t)
		all->s_t = ft_strtrim(li + 1, " ");
	else if (*li == 'F' && *(li + 1) == ' ' && all->floor_col == -1)
		all->floor_col = get_f_and_c_col(ft_strtrim(li + 1, " "));
	else if (*li == 'C' && *(li + 1) == ' ' && all->ceiling_col == -1)
		all->ceiling_col = get_f_and_c_col(ft_strtrim(li + 1, " "));
	else if (is_ident_true(all) && !(*li == 'C' && *(li + 1) == ' '))
		ft_lstadd_back(&all->head, ft_lstnew(all->line));
	else
		exit_err("File is not valid", 12);
	free_is_valid(s, li);
}
