#include "./mlx_beta/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SQ 50
#define KEY_ESC	53
#define KEY_Q 12
#define KEY_W 13
#define KEY_E 14
#define KEY_R 15
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2

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

	int map[ROW][COL];

}				t_cub;

int	input_key(int key, t_cub *game)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W && game->map[game->x - 1][game -> y] != 1)
	{
		game->map[game->x][game->y] = 0;
		game->x = game->x - 1;
		game->map[game->x][game->y] = 2;
	}
	else if (key == KEY_S && game->map[game->x + 1][game -> y] != 1)
	{
		game->map[game->x][game->y] = 0;
		game->x = game->x + 1;
		game->map[game->x][game->y] = 2;
	}
	else if (key == KEY_A && game->map[game->x][game -> y - 1] != 1)
	{
		game->map[game->x][game->y] = 0;
		game->y = game->y - 1;
		game->map[game->x][game->y] = 2;
	}
	else if (key == KEY_D && game->map[game->x][game -> y + 1] != 1)
	{
		game->map[game->x][game->y] = 0;
		game->y = game->y + 1;
		game->map[game->x][game->y] = 2;
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
			if (config == 1)
				game->img.data[(i+k)*(SQ*COL) + l + j] = 0xFFFFFF;
			else if (config == 2)
				game->img.data[(i+k)*(SQ*COL) + l + j] = 0xFF0000;
			else if (config == 0)
				game->img.data[(i+k)*(SQ*COL) + l + j] = 0x000000;
			l++;
		}
		k++;
	}
}

int display (t_cub *game)
{
	int i;
	int j;
	int user_x;
	int user_y;

	i = 0;
	while(i < ROW)
	{
		j = 0;
		while(j < COL)
		{
			if (game->map[i][j] == 1)
				draw_map(game, i, j, 1);
			else if (game->map[i][j] == 2)
			{
				user_y = i;
				user_x = j;
				draw_map(game, i, j, 2);
			}
			else if (game->map[i][j] == 0)
				draw_map(game, i, j, 0);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(game->mlx,game->win,game->img.img,0,0);
	mlx_put_image_to_window(game->mlx,game->win,game->user_img.img,user_x*SQ,user_y*SQ);
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

	mlx_hook(game.win, 2, 0, &input_key, &game);
	mlx_hook(game.win, 17, 0, &k_close, &game);


	mlx_loop_hook(game.mlx,&display ,&game);

	mlx_loop(game.mlx);
}
