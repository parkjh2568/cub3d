#include "./mlx_beta/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SQ 60
#define KEY_ESC	53
#define KEY_Q 12
#define KEY_W 13
#define KEY_E 14
#define KEY_R 15
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define PI 3.14159265358979323846264338327950288419L
#define X_PLAN 1
#define Y_PLAN 2
#define ROW 15
#define COL 20

typedef struct s_img{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_cub{
	void *mlx;
	void *win;
	t_img img;
	t_img user_img;
	t_img mini_map;
	double x;
	double y;
	double dir_x;
	double dir_y;
	double ray_dir_x;
	double ray_dir_y;
	double plan_x;
	double plan_y;
	double old_h;
	int flag;
	int deg;


	int map[ROW][COL];

}				t_cub;

double get_radian(int deg)
{
	return deg * (PI / 180);
}

int	input_key(int key, t_cub *game)
{
	double old_dir_x;
	double old_dir_y;
	double old_plan_x;
	double old_plan_y;
	double rot;

	rot = get_radian(game->deg);
	old_dir_x = game->dir_x;
	old_dir_y = game->dir_y;
	old_plan_x = game->plan_x;
	old_plan_y = game->plan_y;

	double mov_x;
	double mov_y;

	mov_x = (SQ/5) * game->dir_x;
	mov_y = (SQ/5) * game->dir_y;

	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W && game->map[(int)(game->x + mov_x)/SQ][(int)(game->y+mov_y)/SQ] == 0)
	{
		game->x +=  mov_x;
		game->y +=  mov_y;
	}
	else if (key == KEY_S && game->map[(int)(game->x - mov_x)/SQ][(int)(game->y - mov_y)/SQ] == 0)
	{
		game->x -=  mov_x;
		game->y -=  mov_y;	
	}
	else if (key == KEY_A && game->map[(int)(game->x - mov_y)/SQ][(int)(game->y + mov_x)/SQ] == 0)
	{
		game->x -=  mov_y;
		game->y +=  mov_x;	
	}
	else if (key == KEY_D&& game->map[(int)(game->x + mov_y)/SQ][(int)(game->y - mov_x)/SQ] == 0)
	{
		game->x +=  mov_y;
		game->y -=  mov_x;	
	}
	else if (key == KEY_Q)
	{
		game->dir_x = old_dir_x * cos(rot) - old_dir_y * sin(rot);
		game->dir_y = old_dir_x * sin(rot) + old_dir_y * cos(rot);
		game->plan_x = old_plan_x * cos(rot) - old_plan_y * sin(rot);
		game->plan_y = old_plan_x * sin(rot) + old_plan_y * cos(rot);

	}
	else if (key == KEY_E)
	{
		game->dir_x = old_dir_x * cos(rot*-1) - old_dir_y * sin(rot*-1);
		game->dir_y = old_dir_x * sin(rot*-1) + old_dir_y * cos(rot*-1);
		game->plan_x = old_plan_x * cos(rot*-1) - old_plan_y * sin(rot*-1);
		game->plan_y = old_plan_x * sin(rot*-1) + old_plan_y * cos(rot*-1);

	}
	return(0);
}


int k_close(t_cub *game)
{
	exit(0);
}


void draw_player(t_cub *game,int j, int i)
{
	mlx_pixel_put(game->mlx,game->win,(game->y + j)/5,(game->x + i)/5,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,(game->y - j)/5,(game->x - i)/5,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,(game->y + j)/5,(game->x - i)/5,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,(game->y - j)/5,(game->x + i)/5,0xFF0000);

	for(int kk = 8; kk < 20; kk++)
	{
	mlx_pixel_put(game->mlx,game->win,(game->y + game->dir_y * kk)/5,
			(game->x + game->dir_x * kk)/5, 0x0013d8);
	}
}
void draw_map(t_cub *game, int i, int j, int config)
{
	int k, l;

	i = i * SQ/5;
	j = j * SQ/5;

	k = 0;
	l = 0;
	while(k < SQ/5)
	{
		l = 0;
		while (l < SQ/5)
		{
			if (config == 0)
				game->mini_map.data[(i+k)*(SQ/5*COL) + l + j] = 0xFFFFFF;
			else if (config == 1)
				game->mini_map.data[(i+k)*(SQ/5*COL) + l + j] = 0x000000;
			else if (config == 3)
				game->mini_map.data[(i+k)*(SQ/5*COL) + l + j] = 0xffd400;
			else if (config == 4)
				game->mini_map.data[(i+k)*(SQ/5*COL) + l + j] = 0x00ff3d;
			l++;
		}
		k++;
	}
}
void draw_mini_map(t_cub *game)
{
	int i;
	int j;

	i = 0;
	while(i < ROW)
	{
		j = 0;
		while(j < COL)
		{
			if (game->map[i][j] == 1)
				draw_map(game, i, j, 1);
			else if (game->map[i][j] == 0)
				draw_map(game, i, j, 0);
			else if (game->map[i][j] == 3)
				draw_map(game, i, j, 3);
			else if (game->map[i][j] == 4)
				draw_map(game, i, j, 4);
			j++;
		}
		i++;
	}
}

void draw_back_screen(t_cub *game)
{
	int k, l;

	k = 0;
	l = 0;
	while(k < ROW*SQ)
	{
		l = 0;
		while (l < COL*SQ)
		{
			if (k < ROW*SQ/2)
				game->img.data[(k)*(SQ*COL) + l] = 0xffffff;
			else
				game->img.data[(k)*(SQ*COL) + l] = 0xff9729;
			l++;
		}
		k++;
	}
}


void draw_ray(t_cub *game)
{
	int w;

	w = COL*SQ;

	for(int x = 0; x < w; x++)
	{
		double camera = 2 * x / w - 1;
		double ray_dir_x = game->dir_x + game->plan_x * camera;
		double ray_dir_y = game->dir_y + game->plan_y * camera;
		int map_x = (int)game->x;
		int map_y = (int)game->y;
		double side_dist_x;
		double side_dist_y;
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;
		int		step_x;
		int		step_y;

		int		hit = 0;
		int		side;

		unsigned int color;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->y - map_y) * delta_dist_y;
		}
		else
		{
			step_x = 1;
			side_dist_y = (map_y + 1.0 - game->y) * delta_dist_y;
		}

		while (hit == 0)
		{

			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}

			if (game->map[map_x][map_y] > 0)
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = (map_x - game->x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->y + (1 - step_y) / 2) / ray_dir_y;

		int line_height = (int)(ROW*SQ / perp_wall_dist);
		int draw_start = -line_height / 2 + ROW*SQ/2;
		if (draw_start <0)
			draw_start = 0;
		int draw_end = line_height/2 + ROW*SQ/2;
		if (draw_end >= ROW*SQ)
			draw_end = ROW*SQ - 1;

		switch(game->map[map_x][map_y])
		{
			case 1: color = 0x616161; break;
			case 4: color = 0xffd400; break;
			case 3: color = 0x00ff3d; break;
			default: color = 0x000000; break;
		}

		if (side == 1)
			color = color / 2;

		for(int j = draw_start; j < draw_end; j++)
		{
			mlx_pixel_put(game->mlx,game->win,x,j,color);
		}

	}
}


int display (t_cub *game)
{

	int i;
	int j;
	i = 0;
	mlx_put_image_to_window(game->mlx,game->win,game->img.img,0,0);
	draw_ray(game);
	mlx_put_image_to_window(game->mlx,game->win,game->mini_map.img,0,0);
	while(i < SQ/10)
	{
		j = 0;
		while(j < SQ/10)
		{
			draw_player(game,j,i);
			j++;
		}
		i++;
	}

	return(0);
}

int main()
{
	void *mlx;
	void *win;
	t_cub game;

	int ex[ROW][COL] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,4,0,0,2,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,3,0,0,0,0,0,0,0,0,4,0,0,0,3,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	game.dir_x = -1;
	game.dir_y = 0;
	game.plan_x = 0;
	game.plan_y = 0.66;
	game.deg = 10;


	memcpy(game.map,ex,sizeof(int) * COL * ROW);

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, COL*SQ, ROW*SQ, "my_first_mlx");
	game.img.img = mlx_new_image(game.mlx, COL*SQ, ROW*SQ);
	game.mini_map.img = mlx_new_image(game.mlx, COL*SQ/5, ROW*SQ/5);
	game.mini_map.data = (int *)mlx_get_data_addr(game.mini_map.img, &game.mini_map.bpp,
			&game.mini_map.size_l, &game.mini_map.endian);

	game.user_img.img = mlx_xpm_file_to_image(game.mlx, "./zavala.xpm",
			&game.user_img.width,&game.user_img.height); 

	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp,
		   	&game.img.size_l, &game.img.endian);

	game.x = 0;
	game.y = 0;
	while(game.map[(int)game.x][(int)game.y] != 2)
	{
		game.y++;
		if (game.x < ROW && game.y >= COL)
		{
			game.y = 0;
			game.x++;
		}
	}
	game.map[(int)game.x][(int)game.y] = 0;

	game.x = game.x*SQ + SQ/2;
	game.y = game.y*SQ + SQ/2;


	draw_back_screen(&game);
	draw_mini_map(&game);
	mlx_hook(game.win, 2, 0, &input_key, &game);



	mlx_hook(game.win, 17, 0, &k_close, &game);


	mlx_loop_hook(game.mlx,&display ,&game);

	mlx_loop(game.mlx);
}
