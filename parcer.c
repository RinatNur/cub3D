#include "cub3D.h"

void 	init_parcer(t_all *all)
{
	all->no_text = NULL;
	all->so_text = NULL;
	all->we_text = NULL;
	all->ea_text = NULL;
	all->s_text = NULL;
	all->win_w = -1;
	all->win_h = -1;
	all->floor_col = -1;
	all->ceiling_col = -1;
}

void		exit_err(char * str, int code)
{
	write(2, "Error\n", 6);
	write (2, &str, ft_strlen(str));
	write (2, "\n", 1);
	exit (code);
}

int 	is_ident_true(t_all *all)
{
	if (all->no_text && all->so_text && all->we_text && all->ea_text && all->s_text)
//		&& all->floor_col >= 0 && all->ceiling_col >= 0 && all->win_h > 0 && all->win_w > 0)
		return(1);
	return(0);
}

char 	**make_map(t_all *all)
{
	char **map;
	int 	i;
	int 	size;
	t_list *tmp;

	size = ft_lstsize(all->head);
	map = ft_calloc(size + 1, sizeof(char *));
	i = -1;
	tmp = all->head;

	while (tmp) {
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	map[++i] = NULL;
	i = -1;
	return(map);
}

void check_line(t_all *all, char *line)
{
	int i = 0;
	if (!is_ident_true(all))
		while (*line == 32)
			*(line++);
	if (*line == 'N' && *(line + 1) == 'O'){
		all->no_text = line;
		printf("%s\n", all->no_text);
	}
	else if (line[i] == 'S' && line[i+1] == 'O') {
		all->so_text = ft_strtrim(line, " ");
		printf("%s\n", all->so_text);
	}
	else if (line[i] == 'W' && line[i+1] == 'E'){
		all->we_text = ft_strtrim(line, " ");
		printf("%s\n", all->we_text);
			}
	else if (line[i] == 'E' && line[i+1] == 'A') {
		all->ea_text = ft_strtrim(line, " ");
		printf("%s\n", all->ea_text);
	}
	else if (line[i] == 'S' && line[i+1] == ' ') {
		all->s_text = ft_strtrim(line, " ");
		printf("%s\n", all->s_text);
	}
	else if (line[i] == 'F' && line[i+1] == ' '){
		all->floor_col = ft_strtrim(line, ",");
	}
	else if (line[i] == 'C' && line[i+1] == ' ') {
		all->ceiling_col = ft_strtrim(line, ",");
	}
	else if (is_ident_true(all))
		ft_lstadd_back(&all->head, ft_lstnew(all->line));
//	else
//		exit_err("map is not valid", 12);
}

void 	ft_parcer(t_all *all)
{
	init_parcer(all);
	int 	fd;
	int 	i = 0;

	fd = open ("../map.cub", O_RDONLY);
	while ((get_next_line(fd, &all->line)) > 0)
	{
		if (*all->line != '\0')
			check_line(all, all->line);
	}
	if (*all->line != '\0')
		check_line(all, all->line);
	all->map = make_map(all);
	while (all->map[i])
	{
		printf("%s\n", all->map[i]);
		i++;
	}
}

