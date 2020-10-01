#include "cub3D.h"

double	ft_plr_vision(char map_vision)
{
	if (map_vision == 'N')
		return(3 * M_PI / 2);
	else if (map_vision == 'S')
		return(M_PI / 2);
	else if (map_vision == 'E')
		return(0);
	else if (map_vision == 'W')
		return(M_PI);
	return(0);
}

char 	**make_map(t_all *all)
{
	char **map;
	int 	i;
	int 	size;
	t_list *tmp;

	all->fd = open("../map.cub", O_RDONLY);
	while (get_next_line(all->fd, &all->line))
		ft_lstadd_back(&all->head, ft_lstnew(all->line));
	ft_lstadd_back(&all->head, ft_lstnew(all->line));
	size = ft_lstsize(all->head);
	map = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	tmp = all->head;

	while (tmp) {
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	return(map);
}
//
//t_spr_list		*ft_spr_lstnew(int *x, int *y)
//{
//	t_spr_list	*new_el;
//
//	if ((new_el = malloc(sizeof(t_spr_list))))
//	{
//		new_el->spr_x = x;
//		new_el->spr_y = y;
//		new_el->next = NULL;
//		return (new_el);
//	}
//	return (NULL);
//}

//void ft_spr_lstadd_back(t_spr_list **lst, t_spr_list *new)
//{
//	t_spr_list		*last;
//
//	last = *lst;
//	if (!last && lst)
//		*lst = new;
//	else if (lst && new)
//	{
//		while (last->next)
//			last = last->next;
//		last->next = new;
//		new->next = NULL;
//	}
//}

void 	find_plr_sprite(t_all *all)
{
	int 	i;
	int 	j;
	int 	x = 0, y = 0;

	i = 0;
	all->plr_vis = "NSEW";
	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (ft_strchr(all->plr_vis, all->map[i][j]))
			{
				all->plr.x = SCALE * j + (SCALE / 2);
				all->plr.y = SCALE * i + (SCALE / 2);
				all->plr.dir = ft_plr_vision(all->map[i][j]);
			}
			else if (all->map[i][j] == '2')
			{
				x = SCALE * j;
				y = SCALE * i;
				ft_spr_lstadd_back(&all->spr_list, ft_spr_lstnew(&x, &y));
				printf("list.x = %i  list.y = %i\n", all->spr_list->spr_x, all->spr_list->spr_y);
			}
			j++;
		}
		i++;
	}
}
