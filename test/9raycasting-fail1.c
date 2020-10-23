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
#define PI 3.14159265358979323846264338327950288419
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
	int x;
	int y;
	double dir_x;
	double dir_y;
	double ray_dir_x;
	double ray_dir_y;
	double plan_x;
	double plan_y;
	int flag;
	int deg;
	int total_rot;

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
		game->total_rot += 10;
	}
	else if (key == KEY_E)
	{
		game->dir_x = old_dir_x * cos(rot*-1) - old_dir_y * sin(rot*-1);
		game->dir_y = old_dir_x * sin(rot*-1) + old_dir_y * cos(rot*-1);
		game->plan_x = old_plan_x * cos(rot*-1) - old_plan_y * sin(rot*-1);
		game->plan_y = old_plan_x * sin(rot*-1) + old_plan_y * cos(rot*-1);
		game->total_rot -= 10;
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

}

void draw_map(t_cub *game)
{
	int k, l;

	k = 0;
	l = 0;
	while(k < ROW*SQ)
	{
		l = 0;
		while (l < COL*SQ)
		{
				game->img.data[(k)*(SQ*COL) + l] = 0xFFFFFF;
			l++;
		}
		k++;
	}
}

void draw_wall(t_cub *game, int i, int j)
{
	if (game->flag == 1)
			mlx_pixel_put(game->mlx,game->win,i,j,0xff0000);
	else if (game->flag == 3)
			mlx_pixel_put(game->mlx,game->win,i,j,0xffd400);
	else
			mlx_pixel_put(game->mlx,game->win,i,j,0xffd400);
}
void draw_screen(t_cub *game, double ray_x, double ray_y, int plan,int r)
{
	double h;
	double rot;
	double camera;
	double trans_x;
	double trans_y;

	double trans_div;
	int resol_w;
	int resol_h;
	int draw_start;
	int draw_end;

	camera = 2 * r / (SQ * 5) - 1;
	rot = get_radian((game->total_rot) * -1);
	trans_div = game->ray_dir_x / game->ray_dir_y;
	if (plan == X_PLAN)
	{
		trans_x = ray_x - game->x;
		h = fabs(trans_x / game->ray_dir_x);
	}
	else
	{
		trans_y = ray_y - game->y;
		h = fabs(trans_y / game->ray_dir_y);
	}
	resol_w = 1;
	resol_h = (ROW*SQ/h) * SQ;
	draw_start = ROW*SQ/2 - resol_h/2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = ROW*SQ/2 + resol_h/2;
	if (draw_end >= ROW*SQ)
		draw_end = ROW*SQ - 1;
	for(int i = 0;i < resol_w;i++)
	{
		for(int j = draw_start ;j < draw_end ;j++)
		{
			draw_wall(game,i + r*resol_w,j);
		}
	}
}

void draw_ray(t_cub *game)
{
	double ray_x;
	double ray_y;
	double div_x;
	double div_y;
	int w;
	int h;
	double camera;
	double r;
	int plan;
	w = SQ * COL;
	h = SQ * 5;
	plan = 0;
	while(r < w)
	{
		camera = 2 * r / (SQ * COL) - 1;
		div_x = 0;
		div_y = 0;
		ray_x = game->x;
		ray_y = game->y;
		game->ray_dir_x = game->dir_x + game->plan_x * camera;
		game->ray_dir_y = game->dir_y + game->plan_y * camera;
		while(game->map[(int)ray_x/SQ][(int)ray_y/SQ] == 0)
		{
			mlx_pixel_put(game->mlx,game->win,(int)ray_y/5,(int)ray_x/5,0xffd400);
			div_x++;
			div_y++;
			ray_x = game->x + div_x*(game->ray_dir_x);
			if (game->map[(int)ray_x/SQ][(int)ray_y/SQ] == 0)
				plan = X_PLAN;
			ray_y = game->y + div_y*(game->ray_dir_y);
			if (plan == 0 && game->map[(int)ray_x/SQ][(int)ray_y/SQ] == 0)
				plan = Y_PLAN;
		}
		if (plan == X_PLAN)
			ray_y = game->y + div_y*(game->ray_dir_y);
		game->flag = game->map[(int)ray_x/SQ][(int)ray_y/SQ];
		draw_screen(game,ray_x,ray_y,plan,r);
		r++;
	}
}

int display (t_cub *game)
{

	int i;
	int j;
	i = 0;
	mlx_put_image_to_window(game->mlx,game->win,game->img.img,0,0);
	draw_ray(game);
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
	game.total_rot = 0;

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


	draw_map(&game);
	mlx_hook(game.win, 2, 0, &input_key, &game);



	mlx_hook(game.win, 17, 0, &k_close, &game);


	mlx_loop_hook(game.mlx,&display ,&game);

	mlx_loop(game.mlx);
}
