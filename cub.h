/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:59:58 by jheat             #+#    #+#             */
/*   Updated: 2020/10/18 20:16:41 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./mlx_dylib/mlx.h"

# define BPP bits_per_pixel
# define T_NO texture_no
# define T_SO texture_so
# define T_EA texture_ea
# define T_WE texture_we
# define T_S texture_s
# define I img
# define FOV M_PI/3
# define STEP 0.2
# define SCALE (double)64
# define LEFT keycode == 0
# define RIGHT keycode == 2
# define UP keycode == 13
# define DOWN keycode == 1
# define LOOK_L keycode == 123
# define LOOK_R keycode == 124
# define ESC keycode == 53

typedef struct				s_plr {
	double					x;
	double					y;
	double					dir;
	int						flag;
}							t_plr;

typedef struct				s_ray {
	double					x;
	double					y;
	double					dir;
	double					start;
	double					end;
	double					len;
}							t_ray;

typedef struct				s_wall {
	int						start;
	int						end;
}							t_wall;

typedef struct				s_data {
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_data;

typedef struct				s_win
{
	void					*mlx;
	void					*mlx_win;
	t_data					img;
}							t_win;

typedef struct				s_texture {
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	int						width;
	int						height;
}							t_texture;

typedef struct				s_spr_list {
	int						spr_x;
	int						spr_y;
	int						len_from_plr;
	double					spr_dir;
	double					spr_scr_size;
	double					h_offset;
	double					v_offset;
	double					step;
	int						i;
	int						j;
	int						count;
	int						color;
	struct s_spr_list		*next;
}							t_spr_list;

typedef struct				s_all
{
	t_texture				texture_no;
	t_texture				texture_so;
	t_texture				texture_we;
	t_texture				texture_ea;
	t_texture				texture_s;
	t_list					*head;
	t_spr_list				*spr_list;
	t_spr_list				*sprite_list_head;
	t_wall					wall;
	t_ray					ray;
	t_win					win;
	t_plr					plr;
	char					**map;
	char					*line;
	char					*no_t;
	char					*so_t;
	char					*we_t;
	char					*ea_t;
	char					*s_t;
	int						win_w;
	int						win_h;
	int						floor_col;
	int						ceiling_col;
	int						scr_size_x;
	int						scr_size_y;
	int						fd;
	int						x_wall;
	int						y_wall;
	double					x;
	double					y_tmp;
	double					*mas_rays;
}							t_all;

void						draw_img(t_all *all);
void						exit_err(char *str, int code);
int							ft_move(int keycode, t_all *all);
int							get_trgb(int t, int r, int g, int b);
void						my_mlx_pixel_put(t_all *all, int x, int y,
							int color);
int							get_color(t_texture *texture, int x, int y);
void						ft_draw_square(t_all *all, int i, int j,
							double rec_per, int trgb);
void						draw_walls(t_all *all);
void						ray_casting(t_all *all);
void						ft_parcer(t_all *all, int fd);
double						ft_plr_vision(char map_vision);
void						ft_spr_lstadd_back(t_spr_list **lst,
							t_spr_list *new);
t_spr_list					*sort_spr(t_spr_list **ph);
void						get_spr_list(t_all *all, int i, int j);
t_spr_list					*ft_spr_lstnew(int x, int y, int len);
void						check_line(t_all *all, char *line);
void						ft_free_mas(char **mas);
void						free_is_valid(const char *s, char *line);
char						*skip_space(char *line);
void						draw_spr(t_all *all, t_spr_list *sprite);
void						make_screenshot(t_all *all);

#endif
