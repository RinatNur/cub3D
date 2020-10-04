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
	map[++i] = NULL;
	return(map);
}

t_spr_list		*ft_spr_lstnew(int x, int y, int len)
{
	t_spr_list	*new_el;

	if ((new_el = malloc(sizeof(t_spr_list))))
	{
		new_el->spr_x = x;
		new_el->spr_y = y;
		new_el->len_from_plr = len;
		new_el->next = NULL;
		return (new_el);
	}
	return (NULL);
}

void ft_spr_lstadd_back(t_spr_list **lst, t_spr_list *new)
{
	t_spr_list		*last;

	last = *lst;
	if (!last)
		*lst = new;
	else if (new)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->next = NULL;
	}
}

void 	find_plr(t_all *all)
{
	int 	i;
	int 	j;

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
			j++;
		}
		i++;
	}
}

void 		sort_spr(t_spr_list *ph)
{
	t_spr_list *q, *out, *p, *pr;

	out = NULL;
	while (ph)
	{
		q = ph;
		ph = ph->next;
		p = out;
		pr = NULL;
		while (p && q->len_from_plr < p->len_from_plr)
		{
			pr = p;
			p = p->next;
		}
		if (pr == NULL)
		{
			q->next = out;
			out = q;
		}
		else
		{
			q->next = p;
			pr->next = q;
		}
	}
	ph = out;
}

void 		find_spr(t_all *all)
{
	int 	i = 0;
	int 	j;
	int 	x = 0, y = 0, len = 0;

	while (all->map[i])
	{
		j = 0;
		while (all->map[i][j])
		{
			if (all->map[i][j] == '2')
			{
				x = SCALE * j + (SCALE / 2);
				y = SCALE * i + (SCALE / 2);
				len = (int)sqrt((pow(all->plr.x - x, 2) + (pow(all->plr.y - y, 2))));
				ft_spr_lstadd_back(&all->spr_list, ft_spr_lstnew(x, y, len));
			}
			j++;
		}
		i++;
	}
	sort_spr(all->spr_list);
	list_print(all->spr_list);
}
