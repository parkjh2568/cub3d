/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhypar <junhypar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 10:42:11 by junhypar          #+#    #+#             */
/*   Updated: 2020/10/28 20:58:39 by junhypar         ###   ########.fr       */
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
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct	s_img
{
	void		*img;
	int			*data;
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
	t_img		no_w;
	t_img		so_w;
	t_img		we_w;
	t_img		ea_w;
	t_img		sp_w;
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

	int			map[25][25];
}				t_game;

int				get_next_line(int fd, char **line);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
int				ft_strlen(char *str);
char			*ft_strdup(char *src);
char			*ft_strjoin(char *s1, char *s2);
double			get_radian(int deg);
int				display(t_game *g);
void			draw_screen(t_game *g, t_raycast *ray, int r);
void			cub3d(t_game *g);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			free_map(t_game *g);
#endif
