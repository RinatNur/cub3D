#ifndef _CUB_3_D_
# define _CUB_3_D_
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

# define WIN_W 800
# define WIN_H 600
# define FOV M_PI/3
# define SCALE (double)64
# define LEFT keycode == 0
# define RIGHT keycode == 2
# define UP keycode == 13
# define DOWN keycode == 1
# define LOOK_L keycode == 123
# define LOOK_R keycode == 124
# define ESC keycode == 53

typedef struct		s_plr {
	double 		x;
	double 		y;
	double 		dir;
}				t_plr;

typedef struct		s_ray {
	double 		x;
	double 		y;
	double 		dir;
	double 		start;
	double 		end;
	double 		len;
}				t_ray;

typedef struct		s_wall {
	int			start;
	int 		end;
	int 		height;
}				t_wall;

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct s_win
{
	void 		*mlx;
	void 		*mlx_win;
	t_data 		img;
}				t_win;

typedef struct  s_texture {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	int 		width;
	int 		height;
}               t_texture;

typedef struct				s_spr_list {
	int						spr_x;
	int 					spr_y;
	int 					len_from_plr;
	double 					spr_dir;
	double 					spr_scr_size;
	double					h_offset;
	double					v_offset;
	double 					step;
	int 					i;
	int 					j;
	int 					count;
	int 					color;

	struct s_spr_list		*next;
}							t_spr_list;

typedef struct 	s_all
{
	t_texture	texture_NO;
	t_texture	texture_SO;
	t_texture	texture_WE;
	t_texture	texture_EA;
	t_texture	texture_S;

	t_list		*head;
	t_spr_list	*spr_list;
	t_wall		wall;
	t_ray		ray;
	t_win		win;
	t_plr 		plr;
	char 		**map;
	char 		*plr_vis;
	char 		*line;
	//parcing
	char 		*no_text;
	char 		*so_text;
	char 		*we_text;
	char 		*ea_text;
	char 		*s_text;
	int 		win_w;
	int 		win_h;
	int 		floor_col;
	int 		ceiling_col;
	//
	int 		fd;
	int			x_wall;
	int 		y_wall;
	int 		count;
	double 		coef;
	double 		x;
	double 		y_tmp;
	double		*mas_rays;
}				t_all;

void		init_textures(t_all *all);
void 		list_print (t_spr_list *list);
void 		find_spr(t_all *all);
//move.c
int 		ft_move(int keycode, t_all *all);
//colors.c
int 		get_trgb(int t, int r, int g, int b);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int         get_color(t_texture *texture, int x, int y);
//draw.c
void 		init_ray_begin(t_all *all);
void 		ft_draw_square(t_all *all, int i, int j, double rec_per, int trgb);
void		draw_map(t_all *all);
void		draw_img(t_all *all);
void 		one_ray_casting(t_all *all);
void 		ray_casting(t_all *all);
//parcer.c
void 	ft_parcer(t_all *all);
//spr_and_map
double		ft_plr_vision(char map_vision);
char 		**make_map(t_all *all);
t_spr_list		*ft_spr_lstnew(int x, int y, int len);
void 		find_plr(t_all *all);

#endif