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

typedef struct s_img{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct s_cub{
	void *mlx;
	void *win;
	t_img img;
	int x;
	int y;

	int map[6][5];

}				t_cub;

int	input_key(int key, t_cub *game)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W && game->x > 1)
	{
		game->map[game->x][game->y] = 0;
		game->x = game->x - 1;
		game->map[game->x][game->y] = 2;
	}
	else if (key == KEY_S && game->x < 4)
	{
		game->map[game->x][game->y] = 0;
		game->x = game->x + 1;
		game->map[game->x][game->y] = 2;
	}
	else if (key == KEY_A && game->y > 1)
	{
		game->map[game->x][game->y] = 0;
		game->y = game->y - 1;
		game->map[game->x][game->y] = 2;
	}
	else if (key == KEY_D && game->y < 3)
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
				game->img.data[(i+k)*(50*5) + l + j] = 0xFFFFFF;
			else if (config == 2)
				game->img.data[(i+k)*(50*5) + l + j] = 0xFF0000;
			else if (config == 0)
				game->img.data[(i+k)*(50*5) + l + j] = 0x000000;
			l++;
		}
		k++;
	}
}

int display (t_cub *game)
{
	int i;
	int j;

	i = 0;
	while(i < 6)
	{
		j = 0;
		while(j < 5)
		{
			if (game->map[i][j] == 1)
				draw_map(game, i, j, 1);
			else if (game->map[i][j] == 2)
				draw_map(game, i, j, 2);
			else if (game->map[i][j] == 0)
				draw_map(game, i, j, 0);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(game->mlx,game->win,game->img.img,0,0);
	return(0);
}

int main()
{
	void *mlx;
	void *win;
	t_cub game;

	int ex[6][5] = {
	{1,1,1,1,1},
	{1,0,0,0,1},
	{1,0,0,0,1},
	{1,0,2,0,1},
	{1,0,0,0,1},
	{1,1,1,1,1}
	};
	
	memcpy(game.map,ex,sizeof(int) * 5 * 6);

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 500, 600, "my_first_mlx");
	game.img.img = mlx_new_image(game.mlx, 250, 300);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);

	game.x = 0;
	game.y = 0;
	while(game.map[game.x][game.y] != 2)
	{
		game.y++;
		if (game.x <= 5 && game.y > 4)
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
