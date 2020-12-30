/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 10:42:11 by junhypar          #+#    #+#             */
/*   Updated: 2020/12/30 15:01:09 by junhypar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include "./mlx/mlx.h"
# include "./libft/libft.h"

# define _USE_MATH_DEFINES

# define KEY_PRESS 2
# define KEY_RELREASE 3
# define KEY_EXIT_PRESS 17

# define KEY_ESC 53
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT_ARROW 123
# define KEY_RIGHT_ARROW 124

# define X_PLAN 0
# define Y_PLAN 1

# define INPUT_ERROR 1
# define MLX_ERROR 2
# define MAP_FILE_OPEN_ERROR 3
# define GNL_ERROR 4
# define WRONG_MAP 5
# define WRONG_RESOL_INPUT 6
# define WRONG_IMAGE_NAME_INPUT 7
# define WRONG_BG_COLOR_INPUT 8
# define MAP_IS_NOT_AVAILABLE 9
# define SO_MANY_PLAYER_IN_MAP 10
# define ERROR_OF_SAVE 11

# define FLOOR 0
# define CEILLING 1

# define WALL_NUM 5
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S 4

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct	s_old_dig
{
	double		old_dir_x;
	double		old_dir_y;
	double		old_plan_x;
	double		old_plan_y;
}				t_old_dig;

typedef struct	s_img
{
	void		*img;
	int			*data;
	char		*name;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_raycast
{
	int x;
	int y;

	double		dir_x;
	double		dir_y;

	double		side_dist_x;
	double		side_dist_y;

	double		how_long;
	int			wall_height;

	double		delta_x;
	double		delta_y;

	int			step_x;
	int			step_y;

	int			side;
	int			hit;

	double		camera;
	int			plan;
}				t_raycast;

typedef struct	s_painter
{
	int			u_div;
	int			v_div;
	double		v_move;
	int			color;
	int			d_start;
	int			d_end;
	int			d_start_x;
	int			d_end_x;
	int			tex_num;
	double		wall_x;
	double		spt_x;
	double		spt_y;
	double		inv;
	double		trans_x;
	double		trans_y;
	int			spt_screen_x;
	int			v_move_screen;
	int			spt_height;
	int			spt_width;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	double		step;
	int			tex_width;
	int			tex_height;
}				t_painter;

typedef	struct	s_item
{
	double		x;
	double		y;
	int			tex_num;
}				t_item;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		wall[WALL_NUM];

	int			**buf;
	int			**texture;
	double		*z_buf;

	int			save_flag;

	int			key_trig[150];

	t_item		item[100];
	int			item_order[100];
	double		item_dist[100];
	int			item_cnt;

	unsigned int bgcolor[2];

	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;

	double		mov_speed;
	double		rot_speed;

	int			width;
	int			height;
	int			row;
	int			col;

	int			player_cnt;
	double		x;
	double		y;
	int			flag;

	char		*map_all;
	char		**map;
}				t_game;

int				get_next_line(int fd, char **line);
double			get_radian(int deg);
void			ft_error(int err_code, t_game *g);
int				ft_read_map(t_game *g, char *map_name);
int				map_resol(char *out, t_game *g);
int				no_space(char *out, int i);
int				skip_resol_word(char *out, int i, int flag);
int				check_remain(char *out, int i);
int				input_wall_name(char *out, t_game *g, int flag);
int				word_dup(char *out, t_game *g, int i, int flag);
int				input_bg_color(char *out, t_game *g, int flag);
int				find_rest(char *out, int i);
void			free_all(t_game *g);
int				init_map(char *out, t_game *g);
int				map_available_test(t_game *g);
int				map_init_and_available_test(t_game *g);
void			rotate_vector(t_game *g, int deg);
void			ft_start_game(t_game *g);
int				press_key(int key, t_game *g);
int				release_key(int key, t_game *g);
void			ft_key_press_up_down(t_game *g, int flag);
void			ft_key_press_rot_left_right(t_game *g, int flag);
void			ft_key_press_left_right(t_game *g, int flag);
void			key_action(t_game *g);
int				input_esc(t_game *g);
void			ray_casting(t_game *g);
void			put_in_texture(t_game *g);
void			draw_bg(t_game *g);
void			set_painter(t_game *g, t_raycast *ray, t_painter *p);
void			draw_wall(t_game *g, t_raycast *ray, t_painter *p, int j);
void			draw_item(t_game *g);
int				set_bright(int color, t_game *g, int height);
void			start_save_bmp(t_game *g);
#endif
