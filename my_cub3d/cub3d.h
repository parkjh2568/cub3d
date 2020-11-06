/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 10:42:11 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/30 16:42:38 by junhypar         ###   ########.fr       */
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

# define KEY_ESC 53
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define X_PLAN 0
# define Y_PLAN 1

# define INPUT_ERROR 1
# define MLX_ERROR 2
# define MAP_FILE_OPEN_ERROR 3
# define GNL_ERROR 4
# define WRONG_MAP 5
# define WRONG_RESOL_INPUT 6
# define WRONG_NO_WALL_NAME_INPUT 7

# define FLOOR 0
# define CEILL 1

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S 4

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

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

	double		side_x;
	double		side_y;

	double		delta_x;
	double		delta_y;

	int			step_x;
	int			step_y;

	int			hit;

	double		camera;
	int			plan;
}				t_raycast;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		wall[5];
	unsigned int floor;
	unsigned int ceill;

	double		dir_x;
	double		dir_y;
	double		ray_dir_x;
	double		ray_dir_y;
	double		plan_x;
	double		plan_y;

	int			width;
	int			height;
	int			row;
	int			col;
	int			x;
	int			y;
	int			flag;

	double		old_dir_x;
	double		old_dir_y;
	double		old_plan_x;
	double		old_plan_y;

	int			max_long;
	char		*map_all;
	char		**map;

	unsigned int	color[2];
}				t_game;

int				get_next_line(int fd, char **line);
double			get_radian(int deg);
void			ft_error(int err_code);
int				ft_read_map(t_game *g, char *map_name);
int				map_resol(char *out, t_game *g);
void			no_space(char *out, int *i);
int				skip_resol_word(char *out, int *i);
int				check_remain(char *out, int i);
int				map_wall(char *out, t_game *g, int flag);
void			word_dup(char *out, t_game *g, int *i, int flag);
#endif
