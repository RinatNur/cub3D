/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:58:47 by jheat             #+#    #+#             */
/*   Updated: 2020/10/20 17:42:03 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			ft_free_mas(char **mas)
{
	int		i;

	i = -1;
	while (mas[++i])
		free(mas[i]);
	free(mas);
}

void			free_is_valid(const char *s, char *line)
{
	if (*s == 'R' || (*s == 'N' && *(s + 1) == 'O')
		|| (*s == 'S' && *(s + 1) == 'O')
		|| (*s == 'W' && *(s + 1) == 'E') || (*s == 'E' && *(s + 1) == 'A')
		|| *s == 'S' || *s == 'F' || *s == 'C')
		free(line);
}

char			*skip_space(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

void			make_max_size(t_all *all, int i)
{
	if (i == 0)
		all->win_w = all->scr_size_x;
	if (i == 1)
		all->win_h = all->scr_size_y;
}

void			get_scr_value(t_all *all, char **size, int i, int j)
{
	while (size[i])
	{
		while (size[i][j])
			j++;
		if (j > 8)
			make_max_size(all, i);
		else
		{
			if (i == 0)
			{
				all->win_w = ft_atoi(size[0]);
				all->win_w = (all->win_w > all->scr_size_x)
						? all->scr_size_x : all->win_w;
			}
			if (i == 1)
			{
				all->win_h = ft_atoi(size[1]);
				all->win_h = (all->win_h > all->scr_size_y)
						? all->scr_size_y : all->win_h;
			}
		}
		j = 0;
		i++;
	}
}
