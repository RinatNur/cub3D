#include "cub3D.h"

void 	init_parcer(t_all *all)
{
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
}

void		exit_err(char *str, int code)
{
	write(2, "Error\n", 6);
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
	exit (code);
}

int 	is_ident_true(t_all *all)
{
	if (all->no_text && all->so_text && all->we_text && all->ea_text && all->s_text
		&& all->floor_col >= 0 && all->ceiling_col >= 0 && all->win_h >= 0 && all->win_w >= 0)
		return(1);
	return(0);
}

int 	is_space_around_zero(char **map, int i, int j, int end)
{
	char 	c = ' ';
	if (i == 3 && j == 31)
		i = 3;
	if (map[i][j] == '0' && i > 0 && i < end && j > 0 && j < (ft_strlen(map[i]) - 1) &&
			((map[i][j - 1] == c || map[i][j+1] == c) || (map[i - 1][j] == c || map[i - 1][j] == '\0')
			|| (map[i + 1][j] == c || map[i + 1][j] == '\0')))
		return (0);
	return(1);
}

int		is_sprite_out(char **map, int i, int j, int end)
{
	char 	c = ' ';
	if (map[0][j] == '2' || map[end][j] == '2' || map[i][0] == '2' || map[i][ft_strlen(map[i]) - 1] == '2'
		|| (map[i][j] == '2' && i > 0 && i < end && j > 0 && j < (ft_strlen(map[i]) - 1)
		&& ((map[i][j - 1] == c || map[i][j+1] == c) || (map[i - 1][j] == c || map[i - 1][j] == '\0')
		|| (map[i + 1][j] == c || map[i + 1][j] == '\0'))))
		return(0);
	return(1);
}

void 	is_map_valid(t_all *all, char **map)
{
	int i = 0, j = 0;
	int end = 0;
	while (map[end++]);
	end -= 2;
	while (map[i] != NULL)
	{
		while (map[i][j])
		{
			if (ft_strchr(all->map_sym, (int)map[i][j]) && map[0][j] != '0' && map[end][j] != '0'
				&& map[i][0] != '0' && map[i][ft_strlen(map[i]) - 1] != '0'
				&& is_space_around_zero(map, i, j, end) && is_sprite_out(map, i, j, end))
			{

			} else
				exit_err("Not valid map", 2);
			j++;
		}
		j = 0;
		i++;
	}
}

char 	**make_map(t_all *all)
{
	char **map;
	int 	i;
	int 	size;
	t_list *tmp;

	all->map_sym = " 012NSEW\n";
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
//	i = -1;
	is_map_valid(all, map);
	return(map);
}

void 	is_R_or_F_or_C_valid(t_all *all, char *s, char c, int j, char * err)
{
	int i = 0;

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
			while(s[i] == ' ')
				i++;
		j--;
	}
	if (s[i] != '\0')
			exit_err(err, 2);
}

void 	get_scr_size(t_all *all, char *line)
{
	char 	**size;
	int 	i = 0, j = 0;

	line = ft_strtrim(line, " ");
	is_R_or_F_or_C_valid(all, line, ' ', 2, "Not valid screen size");
	size = ft_split(line, ' ');
	while (size[i])
	{
		while(size[i][j])
			j++;
		if (j > 5)
			exit_err("Not valid screen size", 2);
		i++;
	}
	mlx_get_screen_size(all->win.mlx_win, &all->scr_size_x, &all->scr_size_y);

	all->win_w = ft_atoi(size[0]);
	all->win_h = ft_atoi(size[1]);

	all->win_w = (all->win_w > all->scr_size_x) ? all->scr_size_x : all->win_w;
	all->win_h = (all->win_h > all->scr_size_y) ? all->scr_size_y : all->win_h;

//	if (all->win_w < 0 && all->win_h < 0)
//		exit_err("Screen size is not valid", 3);
	i = 0;
}

int		get_F_and_C_col(t_all *all, char *line)
{
	char **rgb;
	int r, g, b, t = 0;

	is_R_or_F_or_C_valid(all, line, ',', 3, "Not valid Floor Or Ceil color");
	rgb = ft_split(line, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		exit_err("Not valid Floor Or Ceil color", 2);
	return (t << 24 | r << 16 | g << 8 | b);
}

void check_line(t_all *all, char *line)
{
	while (*line == ' ')
			*(line++);
	if (*line == 'R' && *(line + 1) == ' ' && all->win_h == -1 && all->win_w == -1 )
		get_scr_size(all, line + 1);
	else if (*line == 'N' && *(line + 1) == 'O' && !all->no_text)
		all->no_text = ft_strtrim(line + 2, " ");
	else if (*line == 'S' && *(line + 1) == 'O' && !all->so_text)
		all->so_text = ft_strtrim(line + 2, " ");
	else if (*line == 'W' && *(line + 1) == 'E' && !all->we_text)
		all->we_text = ft_strtrim(line + 2, " ");
	else if (*line == 'E' && *(line + 1) == 'A' && !all->ea_text)
		all->ea_text = ft_strtrim(line + 2, " ");
	else if (*line == 'S' && *(line + 1) == ' ' && !all->s_text)
		all->s_text = ft_strtrim(line + 1, " ");
	else if (*line == 'F' && *(line + 1) == ' ' && all->floor_col == -1)
		all->floor_col = get_F_and_C_col(all, ft_strtrim(line + 1, " "));
	else if (*line == 'C' && *(line + 1) == ' ' && all->ceiling_col == -1)
		all->ceiling_col = get_F_and_C_col(all, ft_strtrim(line + 1, " "));
	else if (is_ident_true(all) && !(*line == 'C' && *(line + 1) == ' '))//при передаче аргумента С 2-ой раз эта строка не передаётся в мап
		ft_lstadd_back(&all->head, ft_lstnew(all->line));
	else
		exit_err("File is not valid", 12);
}

void 	ft_parcer(t_all *all)
{
	init_parcer(all);
	int 	fd;
	int 	i = 0;

	fd = open ("../map.cub", O_RDONLY);
	while ((get_next_line(fd, &all->line)) > 0)
	{
		if (*all->line != '\0')// || (*all->line == '\0' && all->head))
			check_line(all, all->line);
	}
	if (*all->line != '\0')// || (*all->line == '\0' && all->head))
		check_line(all, all->line);
	all->map = make_map(all);
	while (all->map[i])
	{
		printf("%s\n", all->map[i]);
		i++;
	}
}

