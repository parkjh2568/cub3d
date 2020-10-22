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
#define PI 3.1415926535897

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
	int x;
	int y;
	double dir_x;
	double dir_y;
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
	double rot;

	rot = get_radian(game->deg);
	old_dir_x = game->dir_x;
	old_dir_y = game->dir_y;


	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W && game->map[(game->x-SQ/5)/SQ][game->y/SQ] != 1)
	{
		game->x -= SQ/5;	
	}
	else if (key == KEY_S && game->map[(game->x+SQ/5)/SQ][game->y/SQ] != 1)
	{
		game->x+= SQ/5;
	}
	else if (key == KEY_A && game->map[(game->x)/SQ][(game->y-SQ/5)/SQ] != 1)
	{
		game->y-=SQ/5;
	}
	else if (key == KEY_D&& game->map[(game->x)/SQ][(game->y+SQ/5)/SQ] != 1)
	{
		game->y+=SQ/5;
	}
	else if (key == KEY_Q)
	{
		game->dir_x = old_dir_x * cos(rot) - old_dir_y * sin(rot);
		game->dir_y = old_dir_x * sin(rot) + old_dir_y * cos(rot);
	}
	else if (key == KEY_E)
	{
		game->dir_x = old_dir_x * cos(rot*-1) - old_dir_y * sin(rot*-1);
		game->dir_y = old_dir_x * sin(rot*-1) + old_dir_y * cos(rot*-1);
	}
	return(0);
}


int k_close(t_cub *game)
{
	exit(0);
}

void draw_map(t_cub *game, int i, int j, int config)
{
	int k, l;

	i = i * SQ;
	j = j * SQ;

	k = 0;
	l = 0;
	while(k < SQ)
	{
		l = 0;
		while (l < SQ)
		{
			if (config == 0)
				game->img.data[(i+k)*(SQ*COL) + l + j] = 0xFFFFFF;
			else if (config == 1)
				game->img.data[(i+k)*(SQ*COL) + l + j] = 0x000000;
			l++;
		}
		k++;
	}
}

void draw_player(t_cub *game,int j, int i)
{

	mlx_pixel_put(game->mlx,game->win,game->y + j,game->x + i,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,game->y - j,game->x - i,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,game->y + j,game->x - i,0xFF0000);
	mlx_pixel_put(game->mlx,game->win,game->y - j,game->x + i,0xFF0000);

}

void draw_ray(t_cub *game)
{
	int ray_x;
	int ray_y;
	int div_x;
	int div_y;

	div_x = 0;
	div_y = 0;
	ray_x = game->x;
	ray_y = game->y;
	while(game->map[ray_x/SQ][ray_y/SQ] != 1)
	{
		mlx_pixel_put(game->mlx,game->win,ray_y,ray_x,0xffd400);
		ray_x = game->x + (int)div_x*game->dir_x;
		ray_y = game->y + (int)div_y*game->dir_y;
		div_x++;
		div_y++;
	}
}

int display (t_cub *game)
{

	mlx_put_image_to_window(game->mlx,game->win,game->img.img,0,0);
	int i;
	int j;
	i = 0;
	while(i < SQ/15)
	{
		j = 0;
		while(j < SQ/15)
		{
			draw_player(game,j,i);
			j++;
		}
		i++;
	}
	draw_ray(game);
	return(0);
}

int main()
{
	void *mlx;
	void *win;
	t_cub game;

	int ex[ROW][COL] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1},
	{1,0,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
	{1,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,0,1,0,1,1,0,1,0,1,1,1,1,0,1,1,1,0,0,1},
	{1,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,0,1},
	{1,0,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,0,1},
	{1,0,1,0,1,1,1,0,0,1,0,0,0,0,1,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	game.dir_x = -1;
	game.dir_y = 0;
	game.deg = 10;

	memcpy(game.map,ex,sizeof(int) * COL * ROW);

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, COL*SQ, ROW*SQ, "my_first_mlx");
	game.img.img = mlx_new_image(game.mlx, COL*SQ, ROW*SQ);

	game.user_img.img = mlx_xpm_file_to_image(game.mlx, "./zavala.xpm",&game.user_img.width,&game.user_img.height); 

	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);

	game.x = 0;
	game.y = 0;
	while(game.map[game.x][game.y] != 2)
	{
		game.y++;
		if (game.x < ROW && game.y >= COL)
		{
			game.y = 0;
			game.x++;
		}
	}
	game.map[game.x][game.y] = 0;

	printf("x = %d, y = %d",game.x,game.y);
	game.x = game.x*SQ + SQ/2;
	game.y = game.y*SQ + SQ/2;

	int i;
	int j;

	i = 0;
	while(i < ROW)
	{
		j = 0;
		while(j < COL)
		{
			if (game.map[i][j] == 1)
				draw_map(&game, i, j, 1);
			else if (game.map[i][j] == 0)
				draw_map(&game, i, j, 0);
			j++;
		}
		i++;
	}



	mlx_hook(game.win, 2, 0, &input_key, &game);



	mlx_hook(game.win, 17, 0, &k_close, &game);


	mlx_loop_hook(game.mlx,&display ,&game);

	mlx_loop(game.mlx);
}
